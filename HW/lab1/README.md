# HW1 Secure Interactive Shell

## Configuration
+ /etc/xinetd.d/hw1
+ All the configuration is set exactly the same with the sample except for "server_args".
+ The "euid" and "egid" part are set to '0'. (super user)

## Utility
### All the minimum requirement is implemented, described as follow:
+ cat {file}:              Display content of {file}.
+ cd {dir}:                Switch current working directory to {dir}.
+ chmod {mode} {file/dir}: Change the mode (permission) of a file or directory.
                           {mode} is an octal number.
+ echo {str} [filename]:   Display {str}. If [filename] is given,
  	                       open [filename] and append {str} to the file.
+ exis:                    Leave the shell.
+ find [dir]:              List files/dirs in the current working directory
                           or [dir] if it is given.
                           Minimum outputs contatin file type, size, and name.
+ help:                    Display help message.
+ id:                      Show current euid and egid number.
+ mkdir {dir}:             Create a new directory {dir}.
+ pwd:                     Print the current working directory.
+ rm {file}:               Remove a file.
+ rmdir {dir}:             Remove an empty directory.
+ stat {file/dir}:         Display detailed information of the given file/dir.
+ touch {file}:            Create {file} if it does not exist,
  	                       or update its access and modification timestamp.
+ umask {mode}:            Change the umask of the current session.