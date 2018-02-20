
def computepay(h,r):
    if(h > 40.0):
        return 40*r + (h-40.0)*1.5*r
    else:
        return h*r

hrs = input("Enter Hours:")
rate = input("Enter Rate:")
p = computepay(float(hrs),float(rate))
print(p)