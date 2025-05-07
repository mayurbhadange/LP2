import streamlit as st
import nltk
from nltk.tokenize import word_tokenize
from nltk.corpus import stopwords

# Ensure necessary NLTK data is downloaded
nltk.download('punkt')
nltk.download('stopwords')

# FAQ responses
faq = {
    "hours": "Our store is open from 10 AM to 8 PM, Monday to Saturday.",
    "return": "You can return any item within 30 days of purchase with a receipt.",
    "product": "Yes, we have a wide range of electronics and apparel. What are you looking for?",
    "contact": "You can call us at +1-800-123-4567 or email us at support@retailstore.com",
    "location": "We are located at 123 Main Street, Springfield.",
    "bye": "Thank you for visiting. Have a great day!",
    "hi": "Hello! How can I assist you today?",
}

# Text preprocessing
def preprocessInput(user_input):
    tokens = word_tokenize(user_input.lower())
    filtered = [word for word in tokens if word not in stopwords.words('english')]
    return filtered

# Streamlit UI
st.title("🛍️ Retail Store Chatbot")
st.write("Ask me anything about our store!")

user_input = st.text_input("You:", "")

if user_input:
    words = preprocessInput(user_input)
    matched = False

    for word in words:
        if word in faq:
            st.markdown(f"**🤖 Chatbot:** {faq[word]}")
            matched = True
            break

    if not matched:
        st.markdown("**🤖 Chatbot:** I didn't understand that. Can you please rephrase?")
