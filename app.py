from flask import Flask, render_template, redirect, url_for, request
from pymongo import MongoClient

app = Flask(__name__)
app.config["MONGO_URI"] = "mongodb+srv://mavisonsuz37:12345@cluster0.qvnae20.mongodb.net/ciftlik?retryWrites=true&w=majority&appName=Cluster0"
client = MongoClient(app.config["MONGO_URI"])
db = client['ciftlik']
collection = db['maku']  # Koleksiyon adı güncellendi

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/about')
def about():
    try:
        # Verileri MongoDB'den al
        maku_verileri = list(collection.find({}, {"_id": 0, "kupe_numarasi": 1, "haftalik_sut_verisi": 1}))
        return render_template('about.html', maku_verileri=maku_verileri)
    except Exception as e:
        return str(e)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        # Burada kullanıcı doğrulaması yapılır.
        # Eğer giriş başarılıysa index.html'e yönlendir:
        return redirect(url_for('index'))
    return render_template('login.html')

if __name__ == '__main__':
    app.run(debug=True)
