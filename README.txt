README for the wichtel oracle

The following instructions assume an executable mainWichteln of the C++ code mainWichteln.cpp already existed and was succesfully compiled.

====================================================

INSTRUCTIONS for faster execution of the oracle with a Unix machine:

The program that is created from mainWichteln.cpp, let's say it is mainWichteln,
asks, when run for:
an ENTER to confirm, then the number of partecipants, the minimum circle lenght (again an int), the names of the partecipants and finally a concluding ENTER for confirmation

build a .txt file to atomatize the oracle. This txt file should start with an empty line (first ENTER), then the int with the number of partecipants, then a new line for the min circle length and then the name of each partecipant in a separated line. finally leave an empy line.

assuming the .txt file is called partecipants.txt you can call the oracle with:

./mainWichteln < partecipants.txt

a whole bunch of txt files is created. In each of them there's the mission for a single partecipant.

Have fun!

====================================================

INSTRUCTIONS for execution and usage of the create_names_mail_list.py program.

The python program works if mutt is installed and working with any program capable of sending email. (e.g. msmtp). Additionally it assumes a Unix machine is used.

Given these conditions, the program has several functions, which can be used separately. The three most important ones are:

- separate_names_mails() which creates two lists of Names and Emails

- create_secret_messages(circ, names) which runs mainWichtel using circ as the integer for minimal circle length and names as the list of names of the partecipants.

- send_emails(names, mails) which sends all emails with a predefined email body and the right attachment to the partecipants of the secret santa. The arguments that have to be passed to the function are the list of partecipants and the corrisponding emails (best if taken from separate_names_mails() ).

To initialise the program run it in an interactive console using the list of names and mails as first argument. E.g. from ipython one would use:

run create_names_mail_list.py partecipants.txt

====================================================


