/* global Terminal */
/**
 * Instance of Terminal
 */
(function (root, factory) {
    if (typeof module === 'object' && module.exports) {
        // Node. Does not work with strict CommonJS, but only CommonJS-like
        // environments that support module.exports, like Node.
        module.exports = factory(require('./terminal.js'), 'node')
    } else {
        // Browser globals (root is window)
        root.initTerminal = factory(root.Terminal, 'browser')
    }
}(this, function (Terminal, mode) {
    var commands = {}
    var state = {}

    commands.help = function() {
        var output = "<div>" +
            "<p>Your country is ravaged by political unstability and you are trapped in <strong>The Terminal</strong>. A place in-between Worlds.</p>" +
            "<p>&nbsp;</p>" +
            "<p>Please try to find a way out.</p>" +
            "<p>&nbsp;</p>" +
            "<p>Here are the currently available commands:</p>" +
            "<ul>" +
            "<li><strong>help</strong> - display this help.</li>" +
            "<li><strong>echo &lt;string&gt</strong> - write arguments to the standard output</li>" +
            "<li><strong>exit</strong> - kill terminal process</li>" +
            "<li><strong>su &lt;username&gt</strong> - substitute user identity</li>" +
            "<li><strong>date</strong> - prints the current date and time</li>" +
            "<li><strong>login &lt;username&gt &lt;password&gt</strong> - logs into the remote server</li>" +
            "<li><strong>whoami</strong> - whoami on the remote server</li>" +
            "<li><strong>posts</strong> - posts on the remote server</li>" +
            "<li><strong>newpost &lt;title&gt &lt;body&gt</strong> - creates a new post on the remote server</li>" +
            "<li><strong>motd</strong> - prints the message of the day</li>" +
            "</ul></div>"
        return output
    }

    commands.echo = function (args) {
        args.shift()
        return args.join(' ')
    }

    /**
     * Doom emulator
     */
    commands.iddqd = function () {
        if (!state.iddqd) {
            state.iddqd = true
            return 'Degreelessness mode on'
        } else {
            state.iddqd = false
            return 'Degreelessness mode off'
        }
    }

    /**
     * Is this how you escape?
     */
    commands.escapeplan = function() {
        if (!state.escaped) {
            state.escaped = 1
            return 'You attempt to escape but you slip and fall before you reach the doors.'
        }
        else if (state.escaped == 1) {
            state.escaped = 2
            return 'You are caught and dragged back into the Deluxe Lounge to enjoy a fruit cocktail.'
        }
        else if (state.escaped == 2) {
            state.escaped = 3
            return 'You try to escape but are too lazy to get out of bed.'
        }
        else if (state.escaped == 3) {
            state.escaped = 4
            return "I'm sorry but there's just no escape for you."
        }
        else if (state.escaped == 1337) {
            document.location = "http://" + document.location.hostname + ":4082/escape?target=" + encodeURIComponent(document.origin + "/escaped.html")
            return 'You escape!'
        }
        else {
            state.escaped += 1
            return "Computer says no."
        }
    }

    /**
     * Print the date time
     */
    commands.date = function(args) {
        return "<img src='http://" + document.location.hostname + ":4082/picturise/date' />"
    }

    function httpGet(theUrl)
    {
        var xmlHttp = new XMLHttpRequest();
        xmlHttp.withCredentials = true;
        xmlHttp.open( "GET", theUrl, false ); // false for synchronous request
        xmlHttp.send( null );
        return xmlHttp.responseText;
    }

    function extractMessage(data) {
        j = JSON.parse(data)
        if ("result" in j) {
            return j['result']['message'];
        }
        else {
            return j['error']['message'];
        }
    }

    /**
     * Login to the remote server.
     */
    commands.login = function(args) {
        if (args.length < 3) {
            return "You need to supply a username and password!"
        }
        else {
            var result = httpGet("http://" + document.location.hostname + ":4082/login/" + args[1] + "/" + args[2])
            return extractMessage(result)
        }
    }

    /**
     * Whoami on remote server
     */
    commands.whoami = function(args) {
        var result = httpGet("http://" + document.location.hostname + ":4082/whoami")
        return extractMessage(result)
    }

    /**
     * Logout on remote server
     */
    commands.logout = function(args) {
        var result = httpGet("http://" + document.location.hostname + ":4082/logout")
        return extractMessage(result)
    }

    /**
     * Posts on remote server
     */
    commands.posts = function(args) {
        var result = httpGet("http://" + document.location.hostname + ":4082/posts")
        return extractMessage(result)
    }

    /**
     * Creates a new Post on remote server
     */
    commands.newpost = function(args) {
        if (args.length < 3) {
            return "Please specify a title and a body"
        }
        var theUrl = "http://" + document.location.hostname + ":4082/posts/new"
        var xmlHttp = new XMLHttpRequest();
        var params = "title=" + encodeURIComponent(args[1]) + "&body=" + encodeURIComponent(args[2]);
        xmlHttp.withCredentials = true;
        xmlHttp.open( "POST", theUrl, false ); // false for synchronous request
        xmlHttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
        xmlHttp.send( params );
        var result = xmlHttp.responseText;
        return extractMessage(result)
    }

    /**
     * Posts on remote server
     */
    commands.motd = function(args) {
        var result = httpGet("http://" + document.location.hostname + ":4082/file?filename" + "=motd.txt")
        return extractMessage(result)
    }

    /**
     * Zork emulator
     */
    commands.look = function (args) {
        if (args.length <= 1) {
            return 'You are standing in an open field west of a white house, with a boarded front door. There is a small mailbox here.<br><br>'
        } else {
            if (args[1] == "post_it_note") {
                return "You see a hastily scribbed 'Username: tomhanks, Password: krakozia' written on a crumpled post it note.<br><br>"
            }
            else {
                return 'I don\'t know the word "' + args[1] + '".<br><br>'
            }
        }
    }

    commands.su = function (args) {
        if (args.length > 1) {
            Terminal.user = args[1]
        }
        return ''
    }

    commands.exit = function (args) {
        Terminal.exit()
        console.log('[Process completed]')
    }

    function initTerminal() {
        console.log('Terminal access granted.')

        Terminal.init(document.body, {
            commands: commands,
            prompt: '\\u@\\H $ ',
            intro: '<p>Welcome to The Terminal. Type \'help\' to get started.</p><p>&nbsp;</p>'
        })
    }

    // Return a value to define the module export.
    if (mode === 'node') {
        return {
            initTerminal: initTerminal,
            Terminal: Terminal
        }
    } else {
        return initTerminal
    }
}))
