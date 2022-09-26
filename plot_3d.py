""" plot_3d.py
    Opens file build/output.root, takes specific branch
    to reconstruct a 3D image of the pion's final position
    in the LH2 target.
"""

# pylint: disable=unused-import

import ROOT
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

def set_axes_equal(ax_func):
    """ Make axes of 3D plot have equal scale so that spheres appear as spheres,
        cubes as cubes, etc.. This is one possible solution to Matplotlib's
        ax.set_aspect('equal') and ax.axis('equal') not working for 3D.

    Args:
        ax_func (_type_): a matplotlib axis, e.g., as output from plt.gca().
    """
    x_limits = ax_func.get_xlim3d()
    y_limits = ax_func.get_ylim3d()
    z_limits = ax_func.get_zlim3d()

    x_range = abs(x_limits[1] - x_limits[0])
    x_middle = np.mean(x_limits)
    y_range = abs(y_limits[1] - y_limits[0])
    y_middle = np.mean(y_limits)
    z_range = abs(z_limits[1] - z_limits[0])
    z_middle = np.mean(z_limits)

    plot_radius = 0.5*max([x_range, y_range, z_range])

    ax_func.set_xlim3d([x_middle - plot_radius, x_middle + plot_radius])
    ax_func.set_ylim3d([y_middle - plot_radius, y_middle + plot_radius])
    ax_func.set_zlim3d([z_middle - plot_radius, z_middle + plot_radius])

def data_for_cylinder_along_z(center_x,center_y,radius,height_z):
    """ Creates set of coordinates (X, Y, Z) to draw a cylinder

    Args:
        center_x (double): the X coordinate center of the cylinder
        center_y (double): the Y coordinate center of the cylinder
        radius (double): the radius of the cylinder
        height_z (double): the full height of the cylinder

    Returns:
        x_grid, y_grid, z_grid (ndarray) : set of coordinates of the
                                           cylinder with given properties
    """
    z_vec = np.linspace(0, height_z, 50)-height_z/2
    theta = np.linspace(0, 2*np.pi, 50)
    theta_grid, z_grid=np.meshgrid(theta, z_vec)
    x_grid = radius*np.cos(theta_grid) + center_x
    y_grid = radius*np.sin(theta_grid) + center_y
    return x_grid,y_grid,z_grid

if __name__ == '__main__':

    # ---------- DATA -------------------------------------

    f = ROOT.TFile("res/output.1.root", "read")
    data = f.Get("LH2")
    fX = np.zeros(data.GetEntries(), dtype = float)
    fY = np.zeros(data.GetEntries(), dtype = float)
    fZ = np.zeros(data.GetEntries(), dtype = float)
    for idx, entry in enumerate(data):
        fX[idx] = entry.fX
        fY[idx] = entry.fY
        fZ[idx] = entry.fZ

    Xc,Yc,Zc = data_for_cylinder_along_z(0, 0, 30, 70)

    # ---------- PLOT -------------------------------------

    fig = plt.figure()
    ax = fig.add_subplot(projection='3d')
    ax.scatter(fY[:int(1e5)], fZ[:int(1e5)], fX[:int(1e5)], cmap=plt.viridis(),
               linewidths=0.5, edgecolors='green')

    ax.plot_surface(Yc, Zc, Xc, alpha=0.1)

    set_axes_equal(ax)
    plt.show()
