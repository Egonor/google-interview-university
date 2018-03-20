# Strategy Pattern
#
# http://hingedummy.info/screwinfopage2.htm

class Screw:
    def __init__(self, gauge, threads_per_inch, shaft_length, drive_type):
        self._gauge = gauge
        self._threads_per_inch = threads_per_inch
        self._shaft_length = shaft_length
        self._drive_type = drive_type

        self._screwed_in = False

    def PrintScrewSize(self):
        print("{0}-{1} X {2}", self.gauge, self.threads_per_inch, self.shaft_length)

    def ScrewIn(self):
        self._screwed_in = True



from enum import Enum
# Types of available drivers in an adjustable electric screwdriver
class DriveType(Enum):
    PHILIPS = "Philips" #/Crosshead"
    FLATHEAD = "Slotted/Flathead"
    SQUARE = "Square"
    POZIDRIV = "Pozidriv"

class PowerScrewdriver:
    def __init__(self, Drive_Type):
        self.driver =  Drive_Type

    def ScrewIn(self, screw):
        if self.driver == screw._drive_type:
            screw.ScrewIn()
            print("Should be screwed.")
        else:
            for driver in DriveType:
                if driver == screw._drive_type:
                    self.ChangeDriver(driver)
                    screw.ScrewIn()

            if not screw._screwed_in:
                print("Correct driver unavailable! Grab your wallet!")

    def ChangeDriver(self, Drive_Type):
        self.driver = Drive_Type
        print("New driver is...", self.driver)

s = Screw(8, 32, 1, DriveType.PHILIPS)

sd = PowerScrewdriver(DriveType.FLATHEAD)


sd.ScrewIn(s)

print(s._screwed_in)
print(sd.driver)
