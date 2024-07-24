from sklearn.cluster import KMeans
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import joblib
import os

df1 = pd.read_excel(os.path.join("app/siswa_pelanggar.xlsx"))
df1.head()

def cluster():

    siswa = np.random.randint(20, 41, 100)
    pelanggar =np.random.randint(0,15,100)

    df2 = pd.DataFrame({'siswa': siswa, 'pelanggar': pelanggar})
    df = pd.concat([df1, df2], ignore_index=True)
    df.head()

    X = df[['siswa','pelanggar']]

    sse = []
    for k in range(1, 11):
        kmeans = KMeans(n_clusters=k, random_state=42)
        kmeans.fit(X)
        sse.append(kmeans.inertia_)

    plt.figure(figsize=(10, 6))
    plt.plot(range(1, 11), sse, marker='o')
    plt.title('Elbow Method')
    plt.xlabel('Number of clusters')
    plt.ylabel('SSE')
    plt.show()

    kmeans = KMeans(n_clusters=3, random_state=22)
    kmeans.fit(X)

    df['Cluster'] = kmeans.labels_

    cluster_analysis = df.groupby('Cluster').mean()
    print(cluster_analysis)

    # Optionally, visualize the clusters
    plt.figure(figsize=(10, 6))
    plt.scatter(df['siswa'], df['pelanggar'], c=df['Cluster'], cmap='viridis')
    plt.title('KMeans Clustering')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.show()

    df.head()

    joblib_file = "kmeans_model.pkl"
    joblib.dump(kmeans, joblib_file)
    return 'berhasil'

