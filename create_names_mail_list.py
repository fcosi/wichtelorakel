#!/usr/bin/env python3

"""
script running the wichtel oracle and sending out the emails with mutt!
Author: Filippo G. Cosi
Email: filippo.cosi@ds.mpg.de
"""

import numpy as np
import sys
import os
import glob

try:
    filename = sys.argv[1]
except IndexError:
    filename = input("insert the name of the file you want to split, \
since the argv call went wrong: ")
    print("using {} as filename".format(filename))


def separate_names_mails():
    """
    separates names and mail in a file with with a list made as follows:
    Name Surname <name.surname@email.address.sm>
    
    Returns:
    list of names,
    list of emails
    """
    emails = []
    names = []
    # separate names from emails and save them to differen files
    with open(filename, 'r') as fil:
        for line in fil:
            space_separated = line.split(" ")
            # update the email list
            emails.append(space_separated.pop().rstrip()[1:-1])
            name = ""
            for i in space_separated:
                name = name + i + " "
                # update the names list
            names.append(name.rstrip())
    return names, emails

def save_names_mails(nam, ema):
    """
    save names and emails list to files named "names.txt" and "mails.txt"
    Args:
    nam: list of names
    ema: list of emails
    """
    np.savetxt("names.txt", nam, fmt = "%s")
    np.savetxt("mails.txt", ema, fmt = "%s")

def create_secret_messages(min_circ, names):
    """
    create secret messages using the wichtel oracle and return them as a list
    Args:
    min_circ: minimal circle length
    names: list of partecipants
    """
    
    num_part = len(names)
    if num_part < min_circ:
        min_circ = 2
    
    # in the following the input file for the secret santa program is created
    inputname = "wichtel_input.txt"
    f = open(inputname, 'w')
    f.write("\n{}\n{}\n".format(num_part, min_circ))
    for ind, nam in enumerate(names):
        nam = nam.split(" ")[0]
        f.write(nam + "\n")
    f.write("\n")
    f.close()
    
    # run the wichtel oracle with the newly created input
    os.system('./mainWichteln < {}'.format(inputname))


def send_emails(names, emails):
    """
    send emails to people in names list using mail list
    Args:
    names: list of names
    emails: list of emails
    """
    
    email_body_tmp = """
    Hello dear {}
    
    This is the Secret Santa Oracle. Attached you find a .txt file
    containing the instructions for whom you have to make a present.
    
    This information is top secret and you only know about it, handle it
    with care.  If you don't know what to get as a gift, you might ask
    someone that knows that person well, but be discrete!
    
    Be aware that the price of the present should not be more than 10 Euro.  
    Thank you for your collaboration.
    
    Best regards,
    your
    Secret Santa Oracle
    """
    for ind, nam in enumerate(names):
        nam = nam.split(" ")[0]
        textname = glob.glob("*Wichtel*" + nam + "*.txt")[0]
        email_body = email_body_tmp.format(nam)
        print("sending email to {}: {}".format(nam, emails[ind]))
        os.system('echo "{}" | mutt -a "{}" -s "Wichtel Auftrag / Secret Santa Mission" -- "{}"'.\
                  format(email_body, textname, emails[ind]))


n, e = separate_names_mails()
save_names_mails(n, e)

number_partecipants = len(n)
min_circle = 5




