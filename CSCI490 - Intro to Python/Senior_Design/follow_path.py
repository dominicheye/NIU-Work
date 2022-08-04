# This program will create a rover object.
# The rover will be given a starting point and direction
#
# It will then start moving
# From there it will compare itself against the data 
# from 'GPS.json' to try and match the path
#
# This allows for simulation of the rover, and 
# will allow for easier physical testing because 
# this will give a starting point

import json
import pandas as pd
from pandas import *
import motor_controls as mc
import math

class Rover:
    def __init__(self, lat, long, dir):
        self.lat = lat
        self.long = long
        self.dir = dir
        self.velocity = 0.00002
        self.df = pd.DataFrame(columns = ['Latitude', 'Longitude', 'Direction'])

    def begin_movement(self):
        mc.forward()

    def check_position(self):
        return self.lat, self.long, self.dir
    
    def update_position(self):
        #everything will be normal to 90 or 270 degrees
        #if less than 90, then 90 - dir          ++
        #90 - 180, dir - 90                      -+
        #180 - 270, 270 - dir                    --
        #270 -360, dir - 270                     +-
        if self.dir <= 90:
            dir_norm = 90-self.dir
            velocity_lat = math.sin(dir_norm *math.pi /180) * self.velocity
            velocity_long = math.cos(dir_norm *math.pi /180) * self.velocity

        elif self.dir > 90 and self.dir <= 180:
            dir_norm = self.dir - 90
            velocity_lat = -1*math.sin(dir_norm *math.pi /180) * self.velocity
            velocity_long = math.cos(dir_norm *math.pi /180) * self.velocity

        elif self.dir > 180 and self.dir <= 270:
            dir_norm = 270-self.dir
            velocity_lat =-1* math.sin(dir_norm *math.pi /180) * self.velocity
            velocity_long = -1*math.cos(dir_norm*math.pi /180) * self.velocity

        elif self.dir > 270:
            dir_norm = self.dir -270
            velocity_lat = math.sin(dir_norm *math.pi /180) * self.velocity
            velocity_long =-1* math.cos(dir_norm *math.pi /180) * self.velocity
        self.lat = self.lat + velocity_lat
        self.long = self.long + velocity_long
        self.df.loc[len(self.df.index)] = [self.lat, self.long, self.dir] 

    def move(self, new_lat, new_long):
        x_lat = new_lat - self.lat
        x_long = new_long - self.long

        #negative x_lat means S, positive means N
        #negative x_long means W, positive means E

        #atan(lat/long)

        if x_lat > 0 and x_long > 0:
            dir = 90 - 180 / math.pi * abs(math.atan(abs(x_lat)/abs(x_long)))
        elif x_lat > 0 and x_long < 0:
            dir = 270 + 180 / math.pi * abs(math.atan(abs(x_lat)/abs(x_long)))
        elif x_lat < 0 and x_long > 0:
            dir = 90 + 180 / math.pi * abs(math.atan(abs(x_lat)/abs(x_long)))
        elif x_lat < 0 and x_long < 0:
            dir = 270 - 180 / math.pi * abs(math.atan(abs(x_lat)/abs(x_long)))
        elif x_lat == 0 and x_long != 0:
            dir = (x_long/abs(x_long)) * 90 + 180
        elif x_lat != 0 and x_long == 0:
            dir = (x_lat/abs(x_lat)) * 90 + 90
        else:
            return
        #dir = 180 / math.pi * math.atan2(x_lat, x_long)
        
        if dir < 0:
            dir += 360

        x_dir = self.dir - dir
        if x_dir < 0: 
            mc.right(x_dir)
            self.dir = dir

        elif x_dir > 0:
            mc.left(x_dir)
            self.dir = dir



        mc.forward()
        while abs(self.lat - new_lat) > .001 or abs(self.long - new_long) > .001:
            self.update_position()
            print('')
            print(dir)
            print(self.lat)
            print(new_lat)
            print(abs(self.lat - new_lat))
            print(self.long)
            print(new_long)
            print(abs(self.long - new_long))
        print('')
        print(self.lat)
        print(new_lat)
        print(abs(self.lat - new_lat))
        print(self.long)
        print(new_long)
        print(abs(self.long - new_long))
        print('****************DONE*****************')


    def output(self, filename):
        gps = self.df.to_json(orient="index")
        f = open(filename, "w")
        f.write(gps)
        f.close()
    

f = open('rover1.json')
GPS_data = json.load(f)
f.close()
my_rover = Rover(4156.2744198598, -8846.4584023643,353.21)
my_rover.begin_movement()
last = list(GPS_data)[-1]
last_digit = int(last)

for x in GPS_data:
    y = int(x)
    new_lat = GPS_data[x]['Latitude']
    new_long = GPS_data[x]['Longitude']
    my_rover.move(new_lat, new_long)

my_rover.output('rover2.json')