import matplotlib.pyplot as plt
import sys
import numpy as np
import matplotlib.colors as mcolors

#Para executar: python3 caminho_para_o_arquivo1 caminho_para_o_arquivo2 nome_do_arquivo qtd_de_execuções

file_path = sys.argv[1]
file_path2 = sys.argv[2]
filename = sys.argv[3]
iteration = sys.argv[4]
file_columns = ["Iter","Prob"]

file = np.genfromtxt( file_path, delimiter=';',names= file_columns)
file2 = np.genfromtxt( file_path2, delimiter=';',names= file_columns)

colors = list(mcolors.CSS4_COLORS) 

fig, ax = plt.subplots()
ax.plot(file[file_columns[0]], file[file_columns[1]], marker='o', linestyle='-',color= colors[10], label="Karger")
ax.plot(file2[file_columns[0]], file2[file_columns[1]], marker='o', linestyle='-',color= colors[11], label="Naive Karger")
fig.suptitle((f"Arquivo: {filename} Execuções:{int(iteration)}"))
ax.set(ylabel = "Probabilidade", xlabel = "Iterações")

ax.grid(True)
ax.legend(loc = 'lower right')
plt.show()