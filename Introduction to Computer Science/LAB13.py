#!/usr/bin/python

#
# 21fa-cs115bc
#
# lab13.py
#
# A.Nicolosi
# 20211201
#Nicholas Mohamed
#I plaedge my honor that i have abided by the stveens honor system 
# Practice with classes.

# TODO: Write a bare-bone class InvalidDateError that inherits from ValueError
# Your constructor should allow for up to three argument (for the month,
# day, and year).  Hint: recall the syntax for default parameter values.



# Fill in the missing part in the class Date below
class Date:
	'''
	Date abstraction

	Demonstrate getter/setter methods and operator overloading
	'''
	
	daysInMonth = [31,          # not really using index 0 (dec of prev year)
					31, 28, 31,  # jan, (non-leap) feb, mar
					30, 31, 30,  # apr, may, jun
					31, 31, 30,  # jul, aug, sep
					31, 30, 31]  # oct, nov, dec
	
	def isLeapYear(year):
		# Every fourth year is a leap year,
		# except that every one-hundreth year it isn't,
		# but every four-hundreth year is a leap year after all!
		#
		# TODO
		if year % 400 == 0: return True
		elif year % 100 == 0: return False
		elif year % 4 == 0: return True
		return False
		
	def __init__(self, month=1, day=1, year=1970):
		# Call self.validate to ensure that the parameters
		# make a valid date.  Raise an InvalidDateError if not.
		# If all is good, initialize the attributes _month, _day, and
		# _year
		#
		# TODO
		self.month = month
		self.day = day
		self.year = year
		
	def __repr__(self):
		# Make sure to return a string that looks like a valid
		# call to the class constructor
		# Ex: Date(12, 31, 2021)
		#
		# TODO
		return self.__str__()
		
	def __str__(self):
		# Return a string in the format mm/dd/yyyy
		#
		# TODO
		return '%02d/%02d/%04d' % (self.month, self.day, self.year)
		
	def validateCheckFeb29(self,m, d, y):
		return 2 == m and 29 == d and Date.isLeapYear(y)
	
	def validate_params(self,m, d, y):
		# Return True if m, d, y represent a valid date
		# Start by checking if that's a valid Feb 29 (see
		# helper above); then check if d is a valid day
		# in month m
		#
		# TODO
		if self.validateCheckFeb29(m,d,y): return True
		try:
			return (1<=d) and (d <= self.daysInMonth[m]) and (m>0) and (m<=12)
		except:
			return False
		
	# Write getters and setters
	# TODO: get_month, get_day, get_year, set_month, set_day, set_year
	# NB: Setter should check that the resulting date is valid
	# *before* affecting the change
		
	def get_month(self):
		# TODO
		return self.month
		
	def get_day(self):
		# TODO
		return self.day
		
	def get_year(self):
		# TODO
		return self.year
		
	def set_month(self, month):
		# TODO
		if self.validate_params (month, self.day,self.year): self.month = month
		
	def set_day(self, day):
		# TODO
		if self.validate_params(self.month,day,self.year): self.day = day
		
	def set_year(self, year):
		# TODO
		if self.validate_params(self.moth, self.day, year): self.year = year
		
	# Date arithmetic!
		
	def __eq__(self, other):
		# TODO
		if self.__str__() == other.__str__(): return True
		return False
		
	def __ne__(self, other):
		# TODO
		if __eq__(self,other): return False
		return True
		
	def __lt__(self, other):
		# TODO
		if __eq__(self, other): return False
		elif (self.year > other.year): return False
		elif (self.year < other.year): return True
		elif (self.month < other.month): return True
		elif (self.month > other.month): return False
		elif (self.day > other.day): return False
		elif (self.day < other.day): return True
		return False
		
	def __ge__(self, other):
		# TODO
		if __gt__(self,other) or __eq__(self, other): return True
		return False
		
	def __le__(self, other):
		# TODO
		if __lt__(self, other) or __eq(self, other): return True
		return False
		
	def __gt__(self, other):
		# TODO
		if __lt__(self,other): return False
		if __eq__(self,other): return False
		return True
		
	def __add__(self, deltaInDays):
		'''Computes the date following `self` by the specified number of days'''
		# TODO
		#selfd = Date(self.month, self.day, self.year)
		while deltaInDays > 0:
			if self.validate_params(self.month, self.day + 1, self.year): 
				self.day += 1
			elif self.validate_params(self.month + 1, 1, self.year):
				self.month += 1
				self.day += 1
			else:
				self.month = 1
				self.day = 1
				self.year += 1
			deltaInDays -= 1
		
		
