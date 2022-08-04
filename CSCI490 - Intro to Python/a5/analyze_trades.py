#!/usr/bin/python
# Dominic Heye
# Z1841746


import sys
import senate_stock_trades.compare
import senate_stock_trades.ticker

if len(sys.argv) < 2:
    print("Usage: python analyze_trades.py [ticker <ticker> | compare <senator1> <senator2>]")
    sys.exit()

if sys.argv[1] == "ticker":
    if len(sys.argv) < 3:
        print("Usage: python analyze_trades.py [ticker <ticker> | compare <senator1> <senator2>]")
        sys.exit()
    else:
        count_trades = senate_stock_trades.ticker.count_trades(sys.argv[2])
        sum_trades = senate_stock_trades.ticker.sum_trades(sys.argv[2])
        print("Number of trades:")
        for x in count_trades:
            print(" ", x +":", count_trades[x])
        print("Sum of trade values:")
        for x in sum_trades:
            print(" ",x + ":", "(" + str(sum_trades[x][0]) +", " + str(sum_trades[x][1]) + ")")

elif sys.argv[1] == "compare":
    if len(sys.argv) < 4:
        print("Usage: python analyze_trades.py [ticker <ticker> | compare <senator1> <senator2>]")
        sys.exit()

    else:
        diff_count = senate_stock_trades.compare.count_diff(sys.argv[2], sys.argv[3])
        diff_amount_min, diff_amount_max = senate_stock_trades.compare.amount_diff(sys.argv[2], sys.argv[3])
        if diff_count < 0:
            trade_value = str(diff_count)
        else:
            trade_value = "+" + str(diff_count)

        if diff_amount_min < 0 and diff_amount_max != None:
            range = "-(" + str(abs(diff_amount_min)) + ", " + str(abs(diff_amount_max)) + ")"
        elif diff_amount_min < 0 and diff_amount_max == None:
            range = "-(" + str(abs(diff_amount_min)) + ", " + str(diff_amount_max) + ")"
        else:
            range = "+(" + str(diff_amount_min) + ", " + str(diff_amount_max) + ")"

    print(sys.argv[2] + " has " + trade_value + " trades with value " + range + " than " + sys.argv[3])  
        
else:
    print("Usage: python analyze_trades.py [ticker <ticker> | compare <senator1> <senator2>]")