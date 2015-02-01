from gevent import monkey
monkey.patch_all()

from flask import Flask, render_template, session, request
from flask.ext.socketio import SocketIO, emit, join_room, leave_room, \
    close_room, disconnect

from crontab import CronTab
from datetime import datetime

# cron  = CronTab(user=True)

# # get already created crontab
# for job in cron.find_comment("clock"):
#     if job.hour == hour and job.minute == minute:
#         pass
#     else :
#         #remove old cron
#         cron.remove_all(comment="clock")

# job = cron.new(command="python /home/pi/sunlight_alarm_clock/light/python/transition.py", comment='clock weekday')
# job.hour.on(hour)
# job.minute.on(minute)

# schedule = job.schedule(date_from=datetime.now())
# cron.write()


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
    hour, minute = message["data"].split(":")
    print("New wake up time: {}-{}".format(hour, minute))
    cron  = CronTab(tabfile="test.CronTab")

    # get already created crontab
    for job in cron.find_comment("clock weekday"):
        print(job)
        if job.hour == hour and job.minute == minute:
            pass
        else :
            #remove old cron
            cron.remove_all(comment="clock weekday")
            job = cron.new(command="python /home/pi/sunlight_alarm_clock/light/python/transition.py", comment='clock weekday')
            job.hour.on(hour)
            job.minute.on(minute)
            schedule = job.schedule(date_from=datetime.now())
            import IPython; IPython.embed()
            cron.write("test.CronTab")


@socketio.on('disconnect request', namespace='/test')
def disconnect_request():
    session['receive_count'] = session.get('receive_count', 0) + 1
    emit('my response',
         {'data': 'Disconnected!', 'count': session['receive_count']})
    disconnect()



if __name__ == '__main__':
    socketio.run(app, host="0.0.0.0")
