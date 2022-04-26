
# importing the required module
import matplotlib.pyplot as plt
 
# x axis values
x_neopt = [400, 600, 800, 1000, 1200, 1400]

# corresponding y axis values
y_neopt = [1.383853, 4.929401, 12.115036, 21.033480, 41.016384, 70.628830]
y_opt = [0.418594, 1.898595, 3.986610, 6.214785, 11.850770, 18.817457]
y_blas = [0.038164, 0.125491, 0.279452, 0.547168, 0.917279, 1.419558]

plt.plot(x_neopt, y_neopt, '-ok', color='green', label = "NEOPT")
plt.plot(x_neopt, y_opt, '-ok', color='red', label = "OPT")
plt.plot(x_neopt, y_blas, '-ok', color='blue', label = "BLAS")

# naming the x axis
plt.xlabel('Dimensiune matrice')
# naming the y axis
plt.ylabel('Timp (s)')
 
# giving a title to my graph
plt.title('Analiza comparativa')

#for index in range(len(x_neopt)):
#    plt.text(x_neopt[index], y_blas[index], y_blas[index], size=12)
    
plt.legend()

plt.grid()
 
# function to show the plot
plt.show()