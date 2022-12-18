import matplotlib.pyplot as plt
import numpy as np

results = {
    "Serial": [
        0.000004,
        0.000517,
        0.047132,
        4.253449,
        18.182579 #18.146483 with normal clang
    ],
    "Parallel-1": [
        0.000497, #5
        0.053776, #50
        7.192582, #500
        773.136743, #5000
    ],
    "Parallel-2": [
        0.000842, #5
        0.011546, #50
        1.848244, #500
        98.879020, #5000
    ],
    "Parallel-3": [
        0.000500, #5
        0.053153, #50
        4.924457, #500
        480.847866, #5000
    ],
    "Parallel-1_atomic": [
        0.000490, #5
        0.057810, #50
        7.132220, #500
        715.703122, #5000
    ],
    "Parallel-2_atomic": [
        0.000515, #5
        0.002096, #50
        0.106000, #500
        10.295663, #5000
        42.516322 #10000
    ],
    "Parallel-3_atomic": [
        0.000437,
        0.001292,
        0.072271,
        6.339930, #5000,
        26.288515
    ],
}

image_size_5 = np.array([5,50,500,5000, 10000])
image_size_4 = np.array([5,50,500,5000])

# 6.080122 for parallel-3_atomic and non shared or private keywords

keys = results.keys()

figure_count = 0

for key in keys:
    execution_time = np.array(results.get(key))
    plt.figure(figure_count)
    image_size = None
    if len(results.get(key)) == 4:
        image_size = image_size_4
    else:
        image_size = image_size_5
    plt.plot(image_size, execution_time, marker='o')
    plt.title("Code " + key)
    plt.xlabel("Data Size of One Dimension")
    plt.ylabel("Execution Time (ms)")
    plt.savefig(key + ".png", dpi=300)

    figure_count += 1

plt.show()
a = 5