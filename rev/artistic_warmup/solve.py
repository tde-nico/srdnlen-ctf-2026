import numpy as np
import matplotlib.pyplot as plt

with open("export_results.bin", "rb") as f:
    data = np.frombuffer(f.read(), dtype=np.uint8)

size = 1800
img = data.reshape((len(data)//size, size))

plt.figure()
plt.imshow(img, cmap="gray")
plt.axis("off")
plt.show()
