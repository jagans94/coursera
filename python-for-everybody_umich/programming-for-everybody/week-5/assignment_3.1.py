
hrs = input("Enter Hours:")
h = float(hrs)
rate = input("Enter Rate:")
r = float(rate)


if(h > 40.0):
    print(40.0*r + (h-40.0)*r*1.5)
else:
    print(h*r)