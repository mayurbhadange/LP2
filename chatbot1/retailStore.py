import nltk
print(nltk.__version__)
from nltk.tokenize import word_tokenize
from nltk.corpus import stopwords

try:
    nltk.data.find('tokenizers/punkt')
except LookupError:
    nltk.download('punkt')

try:
    nltk.data.find('corpora/stopwords')
except LookupError:
    nltk.download('stopwords')

faq = {
    "hours": "Our store is open from 10 AM to 8 PM, Monday to Saturday.",
    "return": "You can return any item within 30 days of purchase with a receipt.",
    "product": "Yes, we have a wide range of electronics and apparel. What are you looking for?",
    "contact": "You can call us at +1-800-123-4567 or email us at support@retailstore.com",
    "location": "We are located at 123 Main Street, Springfield.",
    "bye": "Thank you for visiting. Have a great day!",
    "hi": "Hello! How can I assist you today?",
}

def preprocessInput(user_input):
    tokens = word_tokenize(user_input.lower())
    filtered = [word for word in tokens if word not in stopwords.words('english')]
    return filtered

def chatBot():
    print("🤖 Chatbot: Hello! Ask me anything about our store. Type 'exit' to end.\n")
    while True:
        user_input = input("You: ")
        if(user_input.lower() in ['exit', 'bye', 'quit']):
            print(faq["bye"])
            break

        words = preprocessInput(user_input)

        matched = False
        for word in words:
            if word in faq:
                matched = True
                print("🤖 Chatbot: ", faq[word])
                break

        if not matched:
             print("🤖 Chatbot: I didn't understood what you said, can you please rephrase?")

if __name__ == "__main__":
    chatBot()


