import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.naive_bayes import MultinomialNB
import seaborn as sb

# Read data
df = pd.read_csv('spam.csv',encoding = "ISO-8859-1")[['v1', 'v2']]
df.columns = ['label', 'text']
print(df)

# Calculate the ham/spam count
#df.groupby('label').describe()
df.info()
sb.set()
sb.countplot(data = df, x= df["label"]).set_title("Number of ham and spam messages")
plt.show()

