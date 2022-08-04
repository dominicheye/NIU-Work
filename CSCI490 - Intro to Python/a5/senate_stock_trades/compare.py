#!/usr/bin/python

import collections
import senate_stock_trades.util

def count_diff(name_1, name_2):
    senator_count = collections.Counter()
    data = senate_stock_trades.util.get_data()
    for x in data:
        name = x.get("senator")
        if name == name_1:
            senator_count[name_1] += 1
        if name == name_2:
            senator_count[name_2] += 1
    
    count = dict(senator_count)
    count_1 = count.get(name_1)
    count_2 = count.get(name_2)
    difference = count_1 - count_2
    return difference


def amount_diff(name_1, name_2):
    total = {name_1: [0,0], name_2: [0,0]}
    data = senate_stock_trades.util.get_data()
    for x in data:
        name = x.get("senator")
        new_amount = x.get("amount_range")
        if name == name_1 or name == name_2:
            old_sum = total.get(name)
            new_min, new_max = senate_stock_trades.util.add_ammount_ranges(new_amount[0],new_amount[1],old_sum[0],old_sum[1])
            new_dict = {name: [new_min, new_max]}
            total.update(new_dict)
        
    total_1 = total.get(name_1)
    total_2 = total.get(name_2)   
    diff_1, diff_2 = senate_stock_trades.util.sub_ammount_ranges(total_1[0],total_1[1],total_2[0],total_2[1])

    return diff_1, diff_2