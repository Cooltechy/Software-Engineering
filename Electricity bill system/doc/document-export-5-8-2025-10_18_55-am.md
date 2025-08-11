# Electricity Bill App Specification

- User Module -
    - Registration
        - Input - user details {Name , Phone, Address }
        - **Generate Service Number Module** // Helps in generating Unique Service Number
        - **Initialise **// set initial meter reading and balance
        - Output - Unique Service Number
    - IS User Valid
        - input - service number
        - output - true/ false based on service number
- Bill generator - 
    - input - Unique Service Number
        - Current Month Consumption //Calculate usage of current month's electricity
            - Input -curr meter reading
            - Output - Electricity usage , updated meter reading
        - Current Month Charges // Calculate Current Month bill
            - Input - Electricity Usage , rate slab
            - Output - currMonth Charge
        - Total Bill // Calculate Total bill to be paid i.e. adding previous dues also
            - Input - currMonth Charge , previousDues 
            - Output - Total Bill (till currMonth)
    - Output - Bill generated
- Payment-
    - Input - Unique Service Number , Amount
        - Update Bill Status // This will update bill
    - Output - Payment Status , bill status
- Report-
    - Bill Not Paid
        - Input - customer data
        - Output - List of customer who doesn't paid the bill
    - By Service Number
        - Input - Service Number
        - ouput - bill details


---

## User Info
- Name -
- Phone - 
- Address -
- Service Number - (System Generated)
## Bill Info
- Service Number - (ref. to user info)
- CurrMonthReading-
- PrevMonthReading-
- Curr month usage -
- Dues - 
- Curr Month Bill - 
- Total Amount - 
- Last Amt Paid - 


---



## Generate Service Number
- for generating Service number **uuid** is used.
## Initialise(Meter Reading and Amount)
- After Generating of Service Number it bill info is set  to default (for example- CurrMonthReading , PrevMonthReading , All fields are set to 0.)
## Is User Valid
- this function validates the user service is it this exist or not by searching in user database.
- it first checks whether service number is in correct format or not, including length of service number
- for searching we can check each user service number whether this service number match with any existing user or not
- if user exist return true
- else return false








## Bill Generator
- takes service number and validate it then proceeds
## Current Month Usage
- Takes curr month reading and gives curr month electricity usage and updated meter readings
- steps
    - prevmonth reading = currMonth reading
    - currMonthreading = new curr month reading
    - curr month usage = currMonthReading - prevMonth reading
## Current Month Charge
- takes input curr month usage and gives curr month charges
- steps
    - charge = 0 
    - usage > 200
        - usage > 800 charge += (usage - 800) * 10 + 10 , usage = 800
        -  usage > 400 charge += (usage-400) *9.50 + 10 , usage = 400
        - usage > 300 charge += (usage-300)* 9.00 + 10 , usage = 300
        - usage >  200 charge += (usage-200) * 7.70 + 10 , usage = 200
        - charge += usage*5.10 + 10
        - return cahrge
    - usage > 100
        - usage > 100 charge += (usage - 100) * 4.80 + 10 ,  usage = 100 
        - charge += usage * 3.40 + 10
        - return charge
    -  usage > 50 charge += (usage-50)*3.10 + 10 , usage = 50
    -  charge += usage * 1.96 + 10
    - return charge 
## Total Bill
- take currMonth Cahrges and update the bill
- steps 
    - currMonthBill = charge
    - totalBill >0 Dues = totalBill 
    - totalBill = Dues + charge
    - return totalBill 












## Payment
- Takes Service number - validate it then proceed
- takes Amount from user and update bill
    - steps
        - last Amt Paid = amount
        - dues = total Amt - last Amt Paid
        - total Amt = 0
        - bill updated








## Report
### Bill Not Paid
- takes Customer data
    - filtered the customer where totalBill > 10000 or dues > 5000
    - return list of customer whose bill Amt is greater than 10000 or dues is greater than 5000
## By Service Number
- takes service number and validate it then proceed
- displays bill details
## 


## Generate Service Number
## Initialse
## 
## 


