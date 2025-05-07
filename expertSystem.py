def ask_question(question : str) -> bool:
    response = input(question + " :").lower().strip()[0]
    return response == "y"

def diagnose_allergies()->bool:
    return (ask_question("Do you have any itching or swelling?") or ask_question("Do you have watery or red eyes?"))

def diagnose_fever()->bool:
    return (ask_question("Is your body temperature above 37.5 ℃ ?"))

def diagnose_flu()->bool:
    return (ask_question("Do you have fever?") and ask_question("Do you have weakness?") and ask_question("Do you have body aches?"))

def diagnose_cold()->bool:
    return (ask_question("Do you have runny or stuffy nose?") or ask_question("Are you sneezing frequently?"))

def diagnose_appendicities()->bool:
    return (ask_question("Do you have abdominal pain?"))

def diagnose_strep_throat()->bool:
    return (ask_question("Is your throat hurting or swollen?"))

def diagnose_food_poisoning()->bool:
    return (ask_question("Do you feel nauseous?") and ask_question("Have you been vomiting?") and ask_question("Did you experienced loose motions?"))

print(">>>>>>>>>>>>>>>>>>EXPERT SYSTEM TO DIAGNOSE DISEASE<<<<<<<<<<<<<<<<<<<<<")

if diagnose_allergies():
    print("You have allergies!")

if diagnose_appendicities():
    print("you have appendicities!")

if diagnose_cold():
    print("You have cold!")

if diagnose_fever():
    print("You have fever!")

if diagnose_flu():
    print("You have flu!")

if diagnose_food_poisoning():
    print("You have Food poisoning!")

if diagnose_strep_throat():
    print("You have strep throat!")