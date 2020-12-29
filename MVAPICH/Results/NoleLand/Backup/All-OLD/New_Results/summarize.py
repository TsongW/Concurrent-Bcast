import os
import openpyxl


start_rows = [5, 33, 61, 89, 117]
# start_rows['out_4_32'] = 5
# start_rows['out_4_64'] = 33
# start_rows['out_8_32'] = 61
# start_rows['out_8_64'] = 89



def summarize(file_name):
	wb = openpyxl.load_workbook(file_name, data_only=True)
	columns = ['B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T']
	idx=0
	summary = wb['Summary']
	result_c='N'
	
	for sheet in wb.sheetnames:
		if sheet != 'Summary':
			for j in range(len(start_rows)):
				result_r = 0
				for i in range(21):
					if result_r == 3 :
						result_r += 1
					print(i, idx, j, len(columns), len(start_rows))
					summary[columns[idx] + str(i + start_rows[j])].value = wb[sheet][result_c+ str(result_r+start_rows[j])].value
					result_r +=1
		idx += 1
					
	wb.save(file_name)

if __name__ == '__main__':
	summarize('Allgather-MVAPICH-NoleLand.xlsx')
