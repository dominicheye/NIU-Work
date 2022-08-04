#!/usr/bin/python

# This Program will generate random numbers for the recording data program
# It will need to generate a GPS coordinates, cardinal direction,
# and 5 sensor data integers

from random import randint
import pandas as pd
from pandas import DataFrame
import os.path

fname_1 = 'GPS.json'
fname_2 = 'sensor.json'

def generate_GPS_data():
    latitude = randint(-90,90)
    longitude = randint(-180,180)
    direction = randint(0,359)
    return latitude, longitude, direction

def generate_sensor_data():
    sensor_1 = randint(0,1024)
    sensor_2 = randint(0,1024)
    sensor_3 = randint(0,1024)
    sensor_4 = randint(0,1024)
    sensor_5 = randint(0,1024)
    return sensor_1, sensor_2, sensor_3, sensor_4, sensor_5

GPS_df = pd.DataFrame(columns = ['Latitude', 'Longitude', 'Direction'])
sens_df = pd.DataFrame(columns = ['Sensor 1', 'Sensor 2', 'Sensor 3', 'Sensor 4', 'Sensor 5'])

for i in range(1000):
    lat, long, dir = generate_GPS_data()
    GPS_df.loc[len(GPS_df.index)] = [lat, long, dir] 
    sen_1, sen_2, sen_3, sen_4, sen_5 = generate_sensor_data()
    sens_df.loc[len(sens_df.index)] = [sen_1, sen_2, sen_3, sen_4, sen_5] 

GPS_JSON= GPS_df.to_json(orient="index")
sens_JSON = sens_df.to_json(orient="index")

f = open(fname_1, "w")
f.write(GPS_JSON)
f.close()

f = open(fname_2, "w")
f.write(sens_JSON)
f.close()