from gevent import monkey
monkey.patch_all()

from flask import Flask, render_template, session, request
from flask.ext.socketio import SocketIO, emit, join_room, leave_room, \
    close_room, disconnect

app = Flask(__name__)
app.debug = True
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

@app.route('/')
def index():
    return render_template('index.html')

@socketio.on('onConnect', namespace='/test')
def test_connect():
    print("Connected")

@socketio.on('onDisconnect', namespace='/test')
def test_disconnect():
    print('Client disconnected')


@socketio.on('onChangeTime', namespace='/test')
def time_change(message):
    print("New wake up time:", message)

@socketio.on('disconnect request', namespace='/test')
def disconnect_request():
    session['receive_count'] = session.get('receive_count', 0) + 1
    emit('my response',
         {'data': 'Disconnected!', 'count': session['receive_count']})
    disconnect()



if __name__ == '__main__':
    socketio.run(app, host="0.0.0.0")
