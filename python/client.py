import requests

data = requests.get('http://172.20.241.9/luedataa_kannasta_groupid_csv.php?groupid=73').text

with open('file.csv', 'w') as f:
    f.write(data)