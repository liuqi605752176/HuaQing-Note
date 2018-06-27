B =
A = $(B)

#只关心当前有没有赋值，不关心给它赋值的东西有没有内容
ifdef A
success:
	echo "1"
else 
fail:
	echo "2"
endif 
