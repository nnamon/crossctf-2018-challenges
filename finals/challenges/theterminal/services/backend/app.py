#!/usr/bin/python

from flask import Flask, redirect, request, make_response, session
from flask_cors import CORS
import json
import os
from PIL import Image, ImageDraw, ImageFont
import StringIO
import subprocess
import sqlite3

app = Flask(__name__)
app.secret_key = '3R-\x95\x06s\xc0G\x11+\x03\x96\xa5(\x15\xfc\x96Un\xdc\xe8\x05\xa11'
# Enable cross origin sharing for all endpoints
CORS(app, supports_credentials=True)

# Remember to update this list
ENDPOINT_LIST = ['/', '/meta/heartbeat', '/escape', '/picturise', '/login',
                 '/whoami', '/logout', '/posts', '/posts/new', '/file'
                ]

def make_json_response(data, status=True, code=200):
    """Utility function to create the JSON responses."""

    to_serialize = {}
    if status:
        to_serialize['status'] = True
        if data is not None:
            to_serialize['result'] = data
    else:
        to_serialize['status'] = False
        to_serialize['error'] = data
    response = app.response_class(
        response=json.dumps(to_serialize),
        status=code,
        mimetype='application/json'
    )
    return response


@app.route("/")
def index():
    """Returns a list of implemented endpoints."""
    return make_json_response(ENDPOINT_LIST)

@app.route("/meta/heartbeat")
def meta_heartbeat():
    """Returns true"""
    return make_json_response(None)

@app.route("/escape")
def escape():
    """Redirects the user to the escape url"""
    if request.args.get('target'):
        return redirect(request.args.get('target'))
    else:
        return make_json(response([], False))

@app.route("/picturise/<what>")
def pictureise(what):
    """Calls a system command and picturises it."""
    georgia_bold = 'fonts/georgia_bold.ttf'
    georgia_bold_italic = 'fonts/georgia_bold_italic.ttf'
    W, H = (400, 100) # image size
    txt = subprocess.check_output(what, shell=True).strip() # text to render
    background = (0,164,201) # white
    fontsize = 14
    font = ImageFont.truetype(georgia_bold_italic, fontsize)
    image = Image.new('RGBA', (W, H), background)
    draw = ImageDraw.Draw(image)
    w, h = font.getsize(txt)
    draw.text(((W-w)/2,(H-h)/2), txt, fill='white', font=font)
    output = StringIO.StringIO()
    image.save(output, format="PNG")
    contents = output.getvalue()
    output.close()
    response = make_response(contents)
    response.headers.set('Content-Type', 'image/png')
    return response

@app.route("/login/<username>/<password>")
def login(username, password):
    db = sqlite3.connect("database.db")
    results = db.execute("select username, password from accounts;").fetchall()
    for i in results:
        if i[0] == username and i[1] == password:
            session['user'] = username
            return make_json_response({"message": "Thanks for logging in %s" %
                username})
    return make_json_response({"message": "Bad credentials"}, False)

@app.route("/whoami")
def whoami():
    if 'user' in session:
        return make_json_response({"message": "You are %s" % session['user']})
    else:
        return make_json_response({"message": "You are not logged in"}, False)

@app.route("/logout")
def logout():
    if 'user' in session:
        session.pop("user", None)
        return make_json_response({"message": "You are logged out"})
    else:
        return make_json_response({"message": "You are not logged in"}, False)

@app.route("/posts")
def posts():
    if 'user' in session:
        db = sqlite3.connect("database.db")
        results = db.execute("select title, author, body from posts;").fetchall()
        db.close()
        returned = "<p>"
        for i in results:
            returned += "<strong>%s</strong>&nbsp<em>by %s</em>: %s<br />" % i
        returned += "</p>"
        return make_json_response({"message": returned})
    else:
        return make_json_response({"message": "You are not logged in"}, False)

@app.route("/posts/new", methods=["POST"])
def posts_new():
    if 'user' in session:
        if not request.form.get("title") or not request.form.get("body"):
            return make_json_response({"message": "Supply a title and body"}, False)
        db = sqlite3.connect("database.db")
        db.execute("insert into posts values ('%s', '%s', '%s');" % (
            request.form.get("title"), session['user'],
            request.form.get("body")))
        db.commit()
        db.close()
        return make_json_response({"message": "Posted!"})
    else:
        return make_json_response({"message": "You are not logged in"}, False)

@app.route("/file")
def getfile():
    if not request.args.get("filename"):
        return make_json_response({"message": "Need a filename"}, False)
    filecontents = file(request.args.get("filename")).read()
    return make_json_response({"message": filecontents})

if __name__ == '__main__':
    # Change the working directory to the script directory
    abspath = os.path.abspath(__file__)
    dname = os.path.dirname(abspath)
    os.chdir(dname)

    # Run the application
    app.run(debug=False, port=8082, host="0.0.0.0")
