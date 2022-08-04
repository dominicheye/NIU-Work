from gps_class import GPSVis

vis = GPSVis(data_path='rover4.csv',
             map_path='NewHallEast.png',  # Path to map downloaded from the OSM.
             points=(41.94090, -88.77610, 41.93764, -88.77251)) # Two coordinates of the map (upper left, lower right)

vis.create_image(color=(255, 0, 0), width=3)  # Set the color and the width of the GNSS tracks.
vis.plot_map(output='save', save_as= 'rover4.png')

print()
