#!/usr/bin/python

import collections
import senate_stock_trades.util

def count_trades(ticker):
    senator_count = collections.Counter()
    data = senate_stock_trades.util.get_data()
    for x in data:
        if ticker == x.get("ticker"):
            name = x.get("senator")
            senator_count[name] += 1
    
    ticker_count = dict(senator_count)
    return ticker_count

        
def sum_trades(ticker):
    sum_dict = {}
    data = senate_stock_trades.util.get_data()
    for x in data:
        if ticker == x.get("ticker"):
            name = x.get("senator")
            new_amount = x.get("amount_range")
            if name in sum_dict:
                old_sum = sum_dict.get(name)
                new_min, new_max = senate_stock_trades.util.add_ammount_ranges(new_amount[0],new_amount[1],old_sum[0],old_sum[1])
                new_dict = {name: [new_min, new_max]}
                sum_dict.update(new_dict)    
            else:
                sum_dict[name] = new_amount

    return sum_dict
       

                
