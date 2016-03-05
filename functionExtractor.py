#python3 code to get the name of functions in a C file

import sys

if len(sys.argv) < 2:
    exit("No C file recieved")

try:
    f=open(sys.argv[1], 'r')
except:
    exit("Couldn't open file '"+sys.argv[1]+"'")

code = f.read()
#pad the code with newline character
code += '\n'

comment_type = None
in_comment = False
in_function = 0

modified_code=""

for i in range(len(code)):
    if in_comment:
        if comment_type == "inline":
            #Inline comment ends at end of the line
            if code[i] == '\n':
                in_comment = False
                modified_code += '\n'
        else:
            #must be multi-line comment
            if code[i-1:i+1] == '*/':
                in_comment = False
    else:
        if code[i:i+2] in ('//', '/*'):
            #character part of comment - ignore it
            pass
        elif code[i-1:i+1] in ('//', '/*'):
            #comment has started
            if code[i] == '/':
                #Inline comment
                comment_type = "inline"
                in_comment = True
            elif code[i] == '*':
                #multi-line comment
                comment_type = 'multi-line'
                in_comment = True
        else:
            if in_function:
                if code[i] == '}':
                    in_function -= 1
                elif code[i] == '{':
                    in_function += 1
            else:
                if code[i] == '{':
                    in_function += 1
                else:
                    #add the character to the modified code
                    modified_code += code[i]

modified_code = modified_code.split('\n')

#remove preprocessing directives blank lines and variable declarations/function prototypes declerations
for i in range(len(modified_code)-1, -1, -1):
    if modified_code[i] == '' or modified_code[i].startswith('#') or modified_code[i].endswith(';'):
        modified_code.pop(i)

#make sure each line has '(' and ')'
for i in range(len(modified_code)-1, -1, -1):
    if '(' not in modified_code[i] or ')' not in modified_code[i]:
        modified_code.pop(i)

#extract the function type name(assuming they are a single word eg. not "struct st_type function_name()"
return_type = [ line.split()[0] for line in modified_code ]
modified_code = [ ' '.join(line.split()[1:]) for line in modified_code ]

#fetch function name and arguments
function_name = [ line[:line.find('(')].strip() for line in modified_code ]
arguments = [ line[line.find('(')+1:line.rfind(')')].split(',') for line in modified_code ]
argument_type = [ [ argvar.split()[0] if argvar.split() else 'void' for argvar in line ] for line in arguments]

#Print the list of functions as name, return type, and input arguments
for i in range(len(function_name)):
    print('Name :', function_name[i], '\tReturn type :',return_type[i], '\tArguments :',argument_type[i])
