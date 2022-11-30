import credentials as cr
import mysql.connector


mydb = mysql.connector.connect(
  host=cr.host,
  user=cr.user,
  password=cr.password,
  database=cr.database
)

mycursor = mydb.cursor()

mycursor.execute("SELECT * FROM rawdata where groupid = 73")

myresult = mycursor.fetchall()

for x in myresult:
 print(x)
  
