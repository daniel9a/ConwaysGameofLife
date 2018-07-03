# A style-agnostic C indentation checker.
#
# This script only assumes that you are consistent with 
# your indentation standard (e.g. 4 spaces, a tab),
# whether it is a tab, a space, two spaces, and so on.
#
# Other notes:
# 1) The first line that should be indented, that is, the first line
# occurring after a { is treated as the indentation standard
#
# 2) Between every { and the closest new-line or } consists
# only of whitespace.
#


import logging
logging.basicConfig(filename='debugging.log', level=logging.DEBUG, filemode="w",
                    format=('%(filename)s: '
                            '%(levelname)s: '
                            '%(funcName)s(): '
                            '%(lineno)d:\t'
                            '%(message)s'))
import re
import sys


def stripComments(line, commented):
    """Strips C++ and C comments from a line of code"""
    line = line.rstrip()
    # Strip C++ style comments
    line = re.sub(r'//.*$', "", line)
    logging.debug("C++ stripped: " + line)
    # If in commented block and it ends
    if (commented and re.search("\*/", line)):
        logging.debug("");
        return re.sub(r'.*\*/', "", line), False
    # If in commented block, skip line
    elif (commented):
        logging.debug("");
        return "", True
    # If comment begins and ends in line, strip substring
    elif (re.search("/\*", line) and re.search("\*/", line)):
        logging.debug("");
        return re.sub(r'/\*.*\*/', "", line), False
    # If comment begins, strip commented suffix
    elif (re.search("/\*", line)):
        logging.debug("");
        return re.sub(r'/\*.*$', "", line), True
    # Otherwise it's just a line of code
    else:
        logging.debug("");
        return line, commented


def startsWithClosingBrace(line):
    """Returns true iff line starts non-whitespace with a closing brace"""
    return len(line.lstrip()) > 0 and line.lstrip()[0] == '}'

def isBrace(line):
    """Returns true iff line is just a brace"""
    return len(line.strip()) > 0 and (line.strip() == '{' or line.strip() == '}')

class IndentChecker:
    """Checks for consistent indentation of a C program"""

    def __init__(self, filename):
        self.getIndentationStandard(filename)
        self.commented = False
        self.errors = 0
        self.line_number = 0
        self.level = 0


    def formatError(self, error, line, line_number, fatal=False):
        self.errors += 1
        print "Format error: " + error
        print "Line " + str(line_number) + ": \"" + line + "\""
        if fatal:
            print str(self.errors) + " errors found so far"
            sys.exit("Fix this and re-run c_indentation_checker")


    def getIndentationStandard(self, filename):
        """Defines indentation standard as first indentation"""
        self.indentation_level = 0
        self.indentation_standard_string = ""
        self.indentation_type = ""
        first_indentation_line = False
        commented = False
        line_number = 0
        struct_seen = False
        with open(filename) as f:
            for line in f:
                if line.find("struct") != -1 and line.find("typedef") != -1:
                    struct_seen = True
                line_number += 1
                logging.debug("At line " + str(line_number))
                logging.debug("PreStrip: Commented: " + str(commented))
                line, commented = stripComments(line, commented)
                logging.debug("PostStrip: Commented: " + str(commented))
                if first_indentation_line and len(line) > 0:
                    logging.debug("Looking for first indentation on line " + str(line_number) + ": \"" + line + "\"")
                    if line[0] == ' ':
                        logging.debug("First indentation is a space.")
                        self.indentation_type = "Space"
                    elif line[0] == '\t':
                        logging.debug("First indentation is a tab.")
                        self.indentation_type = "Tab"
                    else:
                        sys.exit("Error: indentation expected on line " + str(line_number))
                    indent = line[0 : len(line) - len(line.lstrip())]
                    logging.debug("First indentation length: " + str(len(indent)))
                    break
                elif re.search("{", line):
                    first_indentation_line = True
        if not first_indentation_line:
            if filename[-1] == "h" and not struct_seen:
                print "Finished checking " + filename
                print "0 errors found"
                sys.exit()
            else:
                sys.exit("Error: did not recognize any indented lines.")
        logging.debug("Indentation found on line " + str(line_number))
        standard_string = str(len(indent)) + " " + self.indentation_type
        if len(indent) > 1:
            standard_string += "s" 
        logging.debug("Proceeding with indentation standard of " + standard_string)
        self.indentation_standard_string = indent


    def checkMultiBrace(self, line):
        """Prints an error if more than one of the same type
           of brace exists on this line"""
        if (re.search(r'{.*{', line) or re.search(r'}.*}', line)):
            self.formatError("Multiple braces found", line, self.line_number, True);


    def updateLevel(self, line):
        """Increases or decreases indentation level"""
        logging.debug("checking line: " + line)
        # If { but no }, increase level
        if (re.search("{", line) and not re.search("}", line)):
            logging.debug("opening {")
            self.level += 1
            # If "{ foo...", complain
            if re.search(r'{.*[a-zA-Z].*$', line):
                error = "Alpha characters found after opening brace, put them on a new line"
                logging.debug("{ followed by text found")
                self.formatError(error, line, self.line_number)
        elif (re.search("}", line) and not re.search("{", line)):
            logging.debug("closing }")
            self.level -= 1


    def checkLine(self, line, semicolon_ending_previous_line):
        """Checks format of line, updates level and commented status"""
        self.line_number += 1
        # strip comments and trailing whitespace
        logging.debug("line originally " + line)
        line, self.commented = stripComments(line, self.commented)
        logging.debug("line stripped to " + line)
        line.rstrip()
        if len(line) == 0 or line.isspace():
            return
        self.checkMultiBrace(line)
        indentation_level = self.level
        self.updateLevel(line)
        if startsWithClosingBrace(line):
            indentation_level -= 1
        # Check prefix of line is properly indented whitespace
        logging.debug("Indentation Level: " + str(indentation_level))
        indentation_prefix = ""
        for i in range(0, indentation_level):
            indentation_prefix += self.indentation_standard_string
        error = "Expecting " + str(indentation_level) + " levels of indentation"
        # if no indentation and non-empty line, line must start flush left or be a comment line
        if indentation_level == 0:
            if str.isspace(line[0]) and not self.commented:
                error += ", line starts with whitespace"
                self.formatError(error, line, self.line_number)
        # if indented, check indentation starts after prefix
        elif indentation_level > 0:
            prefix_match = re.match(indentation_prefix, line)
            # indentation doesn't match standard
            if not prefix_match and not line.isspace():
                error += ", line does not match your indentation standard"
                self.formatError(error, line, self.line_number)
            # indentation matches, but whitespace afterwards
            elif prefix_match and str.isspace(line[prefix_match.end()]) and not isBrace(line) and semicolon_ending_previous_line:
                error += ", your indentation starts the line but is followed by extra whitespace"
                self.formatError(error, line, self.line_number)
 

if __name__=="__main__":

    if len(sys.argv) != 2:
        print "Usage: python c_indentation_checker.py filename" 
        sys.exit(0)

    logging.debug("File: " + sys.argv[1])
    print "Checking file " + sys.argv[1] + "..."
    checker = IndentChecker(sys.argv[1])
    no_semicolon_ending = False
    with open(sys.argv[1]) as f:
        for line in f.readlines():
            checker.checkLine(line, not no_semicolon_ending)
            if line[-1] == ';':
                no_semicolon_ending = False
            else:
                no_semicolon_ending = True

    print "Finished checking " + sys.argv[1]
    print str(checker.errors) + " errors found"

