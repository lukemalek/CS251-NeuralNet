#!/usr/bin/python
"""
Simple HTTP server in python, that invokes an executable to handle requests.
Usage::
    ./serve_my_exe.py exe_name
where exe_name is the name of the compiled executable.
Send a POST request::
    curl -d "3ok" http://localhost:25100
"""
from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer
from subprocess import *
import sys, socket, os
# sys.path.insert(0, '/usr/local/cs/cs251')
sys.path.append('/home/users/olaf/pub/cs251')
from port import get_port

exe_name = "a.out"
exe_mtime = -1

def get_top_key(key, yaml):
  if yaml.startswith(key):
    res = yaml
  else:
    pos = yaml.find('\n' + key)
    if -1 == pos:
      return False
    res = yaml[:pos]
  # trim off after newline
  pos2 = res.find('\n')
  if -1 == pos2:
    return res
  res = res[:pos2]
  return res

def load_binary(filename):
    with open(filename, 'rb') as fh:
        return fh.read()

class S(BaseHTTPRequestHandler):
    def _set_headers(self, content):
        self.send_response(200)
        self.send_header('Content-type', content)
        self.send_header('Access-Control-Allow-Origin', '*')
        self.end_headers()

    def do_GET(self):
        if self.path.endswith(".png"):
           self._set_headers('image/png')
           self.wfile.write(load_binary(self.path[1:]))
        
    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        incoming_data = self.rfile.read(content_length)
        # parse the incoming data, to look for some key parts
        if False and len(incoming_data) > 50:
          print >> sys.stderr, "incoming", ord(incoming_data[30]), ord(incoming_data[31]),
        sep = '\n---\n'
        sep_pos = incoming_data.find(sep)
        if -1 == sep_pos:
          yaml_part = ''
        else:
          yaml_part = incoming_data[:sep_pos] + '\n'
        first_name = get_top_key('first_name: ', yaml_part)
        # print >> sys.stderr, first_name,
	global exe_name, exe_mtime
        new_mtime = os.path.getmtime(exe_name)
        is_poll = False
        if new_mtime > exe_mtime:  # restart!
          incoming_data = first_name + sep
          print >> sys.stderr, 'recompiled', 
        else:
          if get_top_key('initialize: ', yaml_part):  # initialization
            incoming_data = first_name + sep
            print >> sys.stderr, 'init_client', 
          elif get_top_key('event_info:', yaml_part):   # user interaction
            print >> sys.stderr, 'event', 
          else: # just a poll
            is_poll = True
        if is_poll:
          outgoing_data = 'same_exe'
        else:
          (stdout, stderr) = Popen('./' + exe_name, stdin=PIPE, stdout=PIPE, stderr=PIPE).communicate(incoming_data)
          outgoing_data = stdout
          if len(stderr) > 0:
            outgoing_data = 'stderr: ' + stderr + chr(0) + outgoing_data
            print >> sys.stderr, stderr
        self._set_headers('text/html')
        self.wfile.write(outgoing_data)
        exe_mtime = new_mtime

    def log_message(self, format, *args):
        sys.stderr.write(".")
        
def run(server_class=HTTPServer, handler_class=S, port=25100):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    hostname = socket.gethostname()
    print 'Starting httpd at', (hostname + ':' + str(port)), 'with', exe_name, '...'
    httpd.serve_forever()

if __name__ == "__main__":
    from sys import argv

    if len(argv) == 3:
        exe_name = argv[1]
        run(port=int(argv[2]))
    elif len(argv) == 2:
    	port = get_port()
        exe_name = argv[1]
        run(port=port)
    elif len(argv) == 1:
    	port = get_port()
        run(port=port)
    else:
        print "Usage: ./serve.py [exe_name] [port]"
