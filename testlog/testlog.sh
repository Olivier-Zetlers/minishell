#The tester : https://github.com/zstenger93/42_minishell_tester.git


# **************************************************************************** #
#                                     PRASING                                  #
# **************************************************************************** #

#---------------------------------------------------------------------------------------------
### Expanding in nested quotation ###

/bin/echo "'$USER'"


#In bash it shows:

#xuewang@f4r12s16:~$ /bin/echo "'$USER'"
#'xuewang'

#while your code shows:

#minishell$ /bin/echo "'$USER'"
#'$USER'

#it only consider 1 layer of quotation, the outermost one

/bin/echo "'"'$USER'"'"

#In bash it shows:

#xuewang@f4r12s16:~$ /bin/echo "'"'$USER'"'"
#'$USER'

#your code shows:

#minishell$ /bin/echo "'"'$USER'"'"
#'xuewang'

#actuallly it's " ' " + '$USER' + " ' " ---> ' (in double quotation, print ' * 1) + $USER (in single quotation so do not expand)' + ' (in double quotation, print ' * 1)
#The quotation end as soon as it found another "

#Similair in this tester
/bin/echo "'$?'"
/bin/echo text"'$USER'" ' $USER '
/bin/echo """""""'"$USER"'"""""""
#---------------------------------------------------------------------------------------------

### escape ###

#Handling "\" : in bash everything after "\" should be printed directly as it wrote https://www.shellscript.sh/escape.html

/bin/echo \$USER
#In bash it shows:

#xuewang@f4r12s16:~$ /bin/echo \$USER
#$USER


#while your code shows:
#minishell$ /bin/echo \$USER
#\xuewang

#---------------------------------------------------------------------------------------------

###"\" collapse in pairs, and order for handling "\"###
# 1 "\", means escape, and shell will collapse the \ when found pairs first
# \\$USER -> collapse, \\->\, so print \$myusername
# \\\$USER ->> collapse, \\ to \ ,\$USER escape do not expand,
# the logic of shell is when detect 2 \, collapse it as one normal "\", now it lose the function as an escape opreator, only a word.
# So when it finish collapsing, even it's one "\" go by a evnp, we do not consider it as an escape opreator, we expand
/bin/echo \\$USER

/bin/echo \\\$USER

/bin/echo \\\\$USER

/bin/echo \\\\\$USER

/bin/echo \\\\\\\\\$USER

/bin/echo \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\$USER \$PATH \\$PWD

#In bash it shows:
#xuewang@f4r12s16:~$ /bin/echo \$USER
#$USER
#xuewang@f4r12s16:~$ /bin/echo \\$USER
#\xuewang
#xuewang@f4r12s16:~$ /bin/echo \\\$USER
#\$USER
#xuewang@f4r12s16:~$ /bin/echo \\\\$USER
#\\xuewang


#While your code shows:

#minishell$ /bin/echo \$USER
#\xuewang
#minishell$ /bin/echo \\$USER
#\\xuewang
#minishell$ /bin/echo \\\$USER
#\\\xuewang
#minishell$ /bin/echo \\\\$USER
#\\\\xuewang
#---------------------------------------------------------------------------------------------

### "\n" missing sometimes ###



#---------------------------------------------------------------------------------------------

###NOT SURE###

#Something killed in tester progress but works well when testing it only in bash

exit 9223372036854775805

exit 123"123"

echo "         |       "  | echo maybe


#---------------------------------------------------------------------------------------------

### STDERR/Exit code ###

#Tester error message:

>| echo sure
#123:	STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ❌ [ minishell(2)  bash(127) ]
cd --
#124:	STD_OUT: ✅  STD_ERR: ❌  EXIT_CODE: ❌ [ minishell(1)  bash(0) ]

echo "         |       "  | echo maybe

#106:	STD_OUT: ❌  STD_ERR: ❌  EXIT_CODE: ✅  

USER

#91:	STD_OUT: ✅  STD_ERR: ❌  EXIT_CODE: ✅ 

" ls"

#92:	STD_OUT: ✅  STD_ERR: ❌  EXIT_CODE: ✅  
" PWD"

#95:	STD_OUT: ✅  STD_ERR: ❌  EXIT_CODE: ✅ 




# **************************************************************************** #
#                                   BUILTINS                                   #
# **************************************************************************** #

#---------------------------------------------------------------------------------------------

###tilde expansion###

# I think it's not requested to spand it in our sujet, so maybe ignore it

echo cd ~

#In bash it shows:

#xuewang@f4r12s16:~$ echo cd ~
#cd /home/xuewang

#while your code shows:

#minishell$ echo cd ~
#cd ~

#---------------------------------------------------------------------------------------------
###ECHO###

# present some same fault as using system /bin/echo when doing echo "'$USER'", but it's because the wrong with quotation handling not echo itself
# -n problen:
# Normally in shell it delete the \n when using -n, -nnnnn, but once some character other than n appears in the line,(here a space), it's not considered as a "delete -n " cmd
# And as quotation parsing is quite on the top ,the bonjour test seems as: "-n" -> -n echo receive : -n-n ,sth not n appear(-) ->do not delete \n
# It seems we need to do quotation parsing first, then send it to echo

echo "-nnnnn "
echo -n"-n" bonjour
echo "-n test1 -n test2"

#In bash it shows:

#xuewang@f4r12s16:~$ echo "-nnnnn "
#-nnnnn 

#while your code shows:

#minishell$ echo "-nnnnn "
#-nnnnn minishell$    <--here you print it and delete the \n at the same time

#when using zsh in your shell it shows:
#minishell$ /bin/echo "-nnnnn "
#-nnnnn 
#minishell$ 

#---------------------------------------------------------------------------------------------

###exit###

#Don't know why the tester kill everything for exit, maybe because it could not detect the status code.
#I copy the the tester's code to run it with echo the status code, it seems the status code are right.
#I enclose it with in the folder(exit_test_echo_status.sh) to run it directly in the root of your shell


#---------------------------------------------------------------------------------------------

###NOT SURE###

#Something killed in tester progress but works well when testing it only in bash
cd ../../
export

#And something pwd
# Your shell successfully go up 2 levels when cd../../, i think the error msg is because the bash will change the prompt when chaning levels, but we do not need to do that
# or because of me not testing them in the same level?

#---------------------------------------------------------------------------------------------


### STDERR/Exit code ###

#Tester error message:
env what
#140:	STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ❌ [ minishell(125)  bash(127) ] 
# and some export
export --TEST=123
#165:	STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ❌ [ minishell(1)  bash(2) ]
export -TEST=100
#170:	STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ❌ [ minishell(1)  bash(2) ] 
export -TEST=123
#185:	STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ❌ [ minishell(1)  bash(2) ] 
export TEST+=100
#200:	STD_OUT: ✅  STD_ERR: ❌  EXIT_CODE: ❌ [ minishell(1)  bash(0) ] 
unset -TEST
#231:	STD_OUT: ✅  STD_ERR: ❌  EXIT_CODE: ❌ [ minishell(0)  bash(2) ]



# **************************************************************************** #
#                                  PIPELINES                                   #
# **************************************************************************** #

#---------------------------------------------------------------------------------------------
###too many pipes###
ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls

#In bash it shows:

# list current directory 

#while your code shows:

# nothing just next line
# and when input new things shows too many files

# Is there a limitation for open files that we have to handle? cause this test is quite extreme

#---------------------------------------------------------------------------------------------
###error message###

ls | cat << stop | ls -la | cat << stop1 | ls | cat << stop2 | ls -la > > out | cat << stop3

#In bash it shows:

#xuewang@f4r12s16:~/ ls | cat << stop | ls -la | cat << stop1 | ls | cat << stop2 | ls -la > > out | cat << stop3
#bash: syntax error near unexpected token `>'


#while your code shows:
#minishell$ ls | cat << stop | ls -la | cat << stop1 | ls | cat << stop2 | ls -la > > out | cat << stop3
#minishell: syntax error near unexpected token `newline'

# > >is illegal, bash thinks it's wrong because token > should not followed by another token > , your minishell thinks there is nothing before >
# Don't think that should be considered as an error it's too detailed?

#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------

###NOT SURE###

#Something killed in tester progress but works well when testing it only in bash

/bin/env | grep "_="
# Run it- a new command -rerun it again, normally it should be a envp that should be renew, but when testing bash gives me the same thing


/bin/env | grep "SHLVL"

# Bash will give the layers number of minishell, so in bash it self, it should be 1 and in minishell, it's a shell in shell, so it is 2
# I think it's right but tester kill it, wired.

#---------------------------------------------------------------------------------------------

### STDERR/Exit code ###

ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls
#1:	STD_OUT: ✅  STD_ERR: ❌  EXIT_CODE: ❌ [ minishell(2)  bash(0) ] 
ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls
#2:	STD_OUT: ❌  STD_ERR: ❌  EXIT_CODE: ✅  
#ls | cat << stop | ls -la | cat << stop1 | ls | cat << stop2 | ls -la > > out | cat << stop3
#29: STD_OUT: ❌  STD_ERR: ✅  EXIT_CODE: ❌ [ minishell(0)  bash(2) ]  
ls|cat Makefile|<wc -l
#35: STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ❌ [ minishell(127)  bash(1) ]
#---------------------------------------------------------------------------------------------


# **************************************************************************** #
#                                    REDIRS                                    #
# **************************************************************************** #

# You've pass all of them

# **************************************************************************** #
#                                     SCMD                                     #
# **************************************************************************** #

###Exit code or error problem###
touch "
"
#seperate 2 lines
#7:	STD_OUT: ✅  STD_ERR: ❌  EXIT_CODE: ❌ [ minishell(2)  bash(0) ]


# **************************************************************************** #
#                                  VARIABLES                                   #
# **************************************************************************** #

### quotation and split ###

# There are a series of "how to deal with space when splitting" quesiton, normally the same problem

#In bash it shows:

#xuewang@f4r12s16:~$ export X="  A  B  "
#xuewang@f4r12s16:~$ /bin/echo $X
#A B
#xuewang@f4r12s16:~$ /bin/echo "1"$X'2'
#1 A B 2

#while your code shows:

#minishell$ export X="  A  B  "
#minishell$ /bin/echo $X
#A B  <---
#minishell$ /bin/echo "1"$X'2'
#1  A  B  2 <--- not act the same

#And zsh shows:
#minishell git:(main) ✗ export X="  A  B  "
#minishell git:(main) ✗ /bin/echo $X
#  A  B  
#minishell git:(main) ✗ /bin/echo "1"$X'2'
#1  A  B  2
#minishell git:(main) ✗ 

# I think you are following the bash splitting rules https://www.gnu.org/software/bash/manual/bash.html#Word-Splitting
# to ignore the spaces before and after the newline, it works well when we only expand X,
# while something changes when we add more things to echo"1"$X'2', your minishell choose not to ignore them now
# Maybe sth with the quotation part?
# for zsh, it seems never ignore spaces and accept the void token 

export X="  A  B  "
/bin/echo "1"$X'2'

export X=" A  B  "
/bin/echo "1"$X'2'

export X="A  B  "
/bin/echo "1"$X'2'

export X="  A  B "
/bin/echo "1"$X'2'

export X="  A  B"
/bin/echo "1"$X'2'

export X="  A B  "
/bin/echo "1"$X'2'

export X="  AB  "
/bin/echo "1"$X'2'

export X="  A  B  "
/bin/echo $X'2'

export X="  A  B  "
/bin/echo $X"1"

export X="   "
/bin/echo "1"$X'2'

export X="  A  B  "
/bin/echo ?$X'2'

export X="  A  B  "
/bin/echo "1"$X?


#---------------------------------------------------------------------------------------------

###NOT SURE###

#Something killed in tester progress but works well when testing it only in bash
/bin/echo "$?"
#during my test with bash it shows the same number

#---------------------------------------------------------------------------------------------

# **************************************************************************** #
#                                  CORRECTION                                  #
# **************************************************************************** #

#in this part it shows some error because it test some same cmds in exit part.
# As mentioned before, I think when I testing it, it works quite well

# **************************************************************************** #
#                                  PATH FAILS                                  #
# **************************************************************************** #

### OLDPWD ###

unset PATH
echo $PATH
/bin/ls
echo 1
cd - #<--
echo 42

#Only difference is your minishell print nothing when "cd -, bash print the oldpwd
# maybe because of the envp OLDPWD? because it went sth wrong with cd - before.

touch tmp_x_file1
tmp_x_file1
echo $?
./tmp_x_file1
echo $?
export PATH=$HOME
echo $PATH
tmp_x_file1
echo $?
./tmp_x_file1
echo $?
unset PATH
tmp_x_file1
echo $?  #<--- Only this one differnt, your result: 127(No such file or directory) bash result : 126(Permission denied)
./tmp_x_file1
echo $?
echo 42
/bin/rm -f tmp_x_file1

#The error conditoin :
#unset PATH, file exist but not executable(only touch)

#---------------------------------------------------------------------------------------------
###NOT SURE###

env -i ./minishell
cd /bin/
ls

#During my test it works as bash
#---------------------------------------------------------------------------------------------
### STDERR/Exit code ###

env -i ./minishell
cd /bin/
ls

#STD_OUT: ❌  STD_ERR: ❌  EXIT_CODE: ✅ 

# **************************************************************************** #
#                                SYNTAX ERRORS                                 #
# **************************************************************************** #



#---------------------------------------------------------------------------------------------

### STDERR/Exit code ###
~
#8:	STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ❌ [ minishell(127)  bash(126) ] 

>echo>
/bin/rm -f echo

#20:	STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ❌ [ minishell(0)  bash(2) ]
<echo<
/bin/rm -f echo

#21:	STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ❌ [ minishell(0)  bash(2) ] 
>>echo>>
/bin/rm -f echo

#22:	STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ❌ [ minishell(0)  bash(2) ] 
#---------------------------------------------------------------------------------------------

# **************************************************************************** #
#                                     WILD                                     #
# **************************************************************************** #

###cmds in void env

echo "env | /usr/bin/wc -l" | env -i $MINISHELL_PATH"/"$EXECUTABLE
echo $?

echo "ls" | env -i $MINISHELL_PATH"/"$EXECUTABLE
echo $?

#For the env -i condition, your minishll will print"minishell: env(or ls): No such file or directory" and could not run
#Bash will run the cmds
#Test with bash cmd :
#echo "env | /usr/bin/wc -l" | env -i bash
#echo "ls" | env -i bash
#---------------------------------------------------------------------------------------------

### STDERR/Exit code ###

echo "unset PATH" | env -i $MINISHELL_PATH"/"$EXECUTABLE
echo $?

#15:	STD_OUT: ❌  STD_ERR: ❌  EXIT_CODE: ✅  
## This one I found it act same as bash
###long test###
echo Lorem ipsum dolor sit amet, consectetur adipiscing elit. Morbi imperdiet orci nec quam lobortis scelerisque. Morbi scelerisque leo molestie justo semper condimentum. Proin hendrerit ut nulla in mattis. Curabitur velit turpis, congue ut aliquam id, condimentum at dolor. Quisque ultricies neque in tellus pretium, vitae porta ipsum vestibulum. Vivamus cursus volutpat diam, at interdum erat fringilla ac. In nisl quam, ultrices vitae cursus ut, aliquam sed lacus. Suspendisse ac turpis fermentum, pulvinar risus quis, molestie elit. Mauris faucibus eget est vitae efficitur. Mauris feugiat enim in posuere auctor. Morbi lorem lorem, pellentesque et viverra vitae, ullamcorper a mauris. Cras blandit pulvinar accumsan. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Aenean id hendrerit elit. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Morbi imperdiet orci nec quam lobortis scelerisque. Morbi scelerisque leo molestie justo semper condimentum. Proin hendrerit ut nulla in mattis. Curabitur velit turpis, congue ut aliquam id, condimentum at dolor. Quisque ultricies neque in tellus pretium, vitae porta ipsum vestibulum. Vivamus cursus volutpat diam, at interdum erat fringilla ac. In nisl quam, ultrices vitae cursus ut, aliquam sed lacus. Suspendisse ac turpis fermentum, pulvinar risus quis, molestie elit. Mauris faucibus eget est vitae efficitur. Mauris feugiat enim in posuere auctor. Morbi lorem lorem, pellentesque et viverra vitae, ullamcorper a mauris. Cras blandit pulvinar accumsan. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Aenean id hendrerit elit.
#16:	STD_OUT: ❌  STD_ERR: ❌  EXIT_CODE: ❌ [ minishell(127)  bash(0) ] 



# **************************************************************************** #
#                                leaks                                         #
# **************************************************************************** #
#Only 2 leaks it's really great! I like the idea of safe_malloc

echo "         |       "  | echo maybe # in parsing hell file

106:	STD_OUT: ❌  STD_ERR: ❌  EXIT_CODE: ✅  LEAKS: cat: tmp_valgrind-out.txt: No such file or directory❌ 

unset TES{T # in builtin file

224:	STD_OUT: ✅  STD_ERR: ✅  EXIT_CODE: ✅  LEAKS: ❌