#! usr/bin/python

import pandas as pd
import csv

lat_neg = 0
long_neg = 0

df = pd.read_json("rover4.json")

list_of_lists = []

for i in df:
   lat = float(df.iat[0, i]) / 100
   long = float(df.iat[1, i]) /100

   lat = str(lat)
   long = str(long)
   
   if lat[0] == '-':
      lat_neg = 1
   if long[0] == '-':
      long_neg = 1

   lat_degree = float(lat[:2+lat_neg])
   long_degree = float(long[:2+long_neg])

   lat_seconds = float(lat[2+lat_neg:])
   long_seconds = float(long[2+long_neg:])

   lat_seconds = lat_seconds*100
   long_seconds = long_seconds *100
   if lat_neg == 0:
      lat = lat_degree + lat_seconds/60
   
   else:
      lat = lat_degree - lat_seconds/60
   
   if long_neg == 0:
      long = long_degree + long_seconds/60
   
   else:
      long = long_degree - long_seconds/60


   lister = [lat, long]
   list_of_lists.append(lister)
   


with open('rover4.csv', 'w') as csvfile:
    write = csv.writer(csvfile)
    write.writerows(list_of_lists)

