from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route("/run_python_script", methods=["POST"])
def run_python_script():
    data = request.get_json()
    script_file = data["code_two_way.py"]
    result = subprocess.run(["python", script_file], stdout=subprocess.PIPE)
    return result.stdout.decode("utf-8")

if __name__ == "__main__":
    app.run()