#!/usr/bin/env python3

import yaml
import json

fh = open("test.yaml", "r", encoding="utf-8")
text = fh.read()
data = yaml.load(text, Loader=yaml.FullLoader)

print("YAML Dump:")
print(yaml.dump(data, sort_keys=False))  # see more: help(yaml.Dumper)

# refer to https://stackoverflow.com/questions/53757981/converting-yaml-to-jsontypeerror-object-of-type-date-is-not-json-serializabl
import datetime
def DateEncoder(obj):
    if isinstance(obj, (datetime.datetime, datetime.date)):
        return obj.strftime('%Y-%m-%d')

print("JSON Dump:")
print(json.dumps(data, indent=4, default=DateEncoder))

