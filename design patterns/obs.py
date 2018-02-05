# Basic Observer Pattern Example

class Radio: # Subject
    def __init__(self):
        self._station_name = '103.5 Obs FM'
        self._listeners = []

    def attach(self, listener):
        if listener not in self._listeners:
            self._listeners.append(listener)
            print("+++", listener, "tuned into", self._station_name)
        else:
            print(listener, "is already listening!")

    def detach(self, listener):
        self._listeners.remove(listener)
        print("---", listener, "tuned out... :(")

    def notify(self, song_title):
        print("\nNEW SONG:")
        for listener in self._listeners:
            listener.update(song_title)

class Listener: # Observer
    def __init__(self, user_name):
        self._user_name = user_name

    def update(self, song_title):
        print(self._user_name, "is listening to", song_title)

# Tests
feed = Radio()

ben = Listener('Benny B')                       # Create an observer
feed.attach(ben)                                # Attach first observer
alex = Listener('Monkhay!')
feed.attach(alex)                               # Attach second observer

feed.notify('Fuse - Knights of Explodinya')     # Update Subject
feed.attach(ben)                                # Reattach observer (fails)
feed.notify('Jelton Yon - Little Lady Groovin\'')
feed.detach(alex)                               # Detach an observer
feed.notify('BAAB - The Y\'')