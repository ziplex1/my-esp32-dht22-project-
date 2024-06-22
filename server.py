from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/data', methods=['POST'])
def receive_data():
    data = request.json
    if 'temperature' in data and 'humidity' in data:
        temperature = data['temperature']
        humidity = data['humidity']
        print(f"Received temperature: {temperature}, humidity: {humidity}")
        return jsonify({"status": "success", "temperature": temperature, "humidity": humidity}), 200
    else:
        return jsonify({"status": "fail", "message": "Invalid data"}), 400

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
