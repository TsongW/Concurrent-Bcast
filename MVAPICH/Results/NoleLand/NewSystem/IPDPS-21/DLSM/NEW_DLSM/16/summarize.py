import os
import openpyxl


start_rows = [5, 34, 63, 92]


def summarize(file_name):
	wb = openpyxl.load_workbook(file_name, data_only=True)
	columns = ['B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S']
	idx=0
	summary = wb['Summary']
	result_c='O'
	
	for sheet in wb.sheetnames:
		if sheet != 'Summary':
			for j in range(len(start_rows)):
				result_r = 0
				for i in range(22):
					summary[columns[idx] + str(i + start_rows[j])].value = wb[sheet][result_c+ str(result_r+start_rows[j])].value
					result_r +=1
		idx += 1
					
	wb.save(file_name)

if __name__ == '__main__':
	summarize('NS-DLSM.xlsx')