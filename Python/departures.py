#Jasmit Singh TUTORWORKS programming task
import requests

#variables to hold values
origin = 'PLZA'
direction = 'S'
api_key = 'MW9S-E7SL-26DU-VV8V'
cmd = 'etd'

#get reuqest from api and store in a JSON
r = requests.get("http://api.bart.gov/api/etd.aspx?cmd=%s&orig=%s&dir=%s&key=%s&json=y" % (cmd, origin, direction, api_key))

#array that stores different times
array = []

#number of trains departing from current location
trains = len(r.json()['root']['station'][0]['etd'])

#if theres no trains print emppty array else print minutes the minutes left for each
if trains == 0 :
    print(array)
else :
    for x in range(trains):
        for y in range(len(r.json()['root']['station'][0]['etd'][x]['estimate'])):
            
            if r.json()['root']['station'][0]['etd'][x]['estimate'][y]['minutes'].isnumeric() :
                array.append(int(r.json()['root']['station'][0]['etd'][x]['estimate'][y]['minutes']))
            else :
                print('The value in minutes is non numeric') 
    print(array)
