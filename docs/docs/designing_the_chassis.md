---
layout: default
title: Designing the Chassis
nav_order: 5
#parent: ..
#has_children: ...
---

# Designing the Chassis
{: .no_toc }

<details open markdown="block">
  <summary>
    Table of contents
  </summary>
  {: .text-delta }
1. TOC
{:toc}
</details>

## CAD Software
CAD (or Computer-Aided Design) software, such as Fusion 360 or SolidWorks, allows us to create 3D models which can then be manufactured. For the self-balancing robot, we will be using Fusion 360 to design the chassis.


### Fusion 360
1. To install Fusion 360 (Education License), click <a href="https://www.autodesk.com/campaigns/education/fusion-360" target="_blank">here</a>. This will take you to the Fusion 360 educational site.
2. Click 'Get Fusion 360'.
![Get Fusion 360](../../assets/designing_the_chassis/fusion/fusion_1.png)
3. Then click 'Sign in', located in the top right corner.
![Sign in](../../assets/designing_the_chassis/fusion/fusion_5.png)
4. If you don't already have an Autodesk account, create a new account. Otherwise, sign in.
![Sign in](../../assets/designing_the_chassis/fusion/fusion_6.png)
![Create new account](../../assets/designing_the_chassis/fusion/fusion_7.png)
5. Once you are signed in, click 'Get Educational Access'.
![Get Educational Access](../../assets/designing_the_chassis/fusion/fusion_3.png)
6. Fill out your details and confirm.
![Fill out details](../../assets/designing_the_chassis/fusion/fusion_4.png)
7. You should now have educational access!
![Confirmed](../../assets/designing_the_chassis/fusion/fusion_8.png)
8. To download Fusion 360, click 'Get product' then 'Access'. This will take you to a separate page where the client will download automatically. 
![Get product](../../assets/designing_the_chassis/fusion/fusion_9.png)
9. Click on the client to finish installing.
![Client.exe](../../assets/designing_the_chassis/fusion/fusion_10.png)

{: .highlight }
> Tip: To check that the Fusion you have installed is the education version, run the application. It should say 'Autodesk Fusion 360 (Educational License)' in the top left corner.


## Design Considerations
While designing your chassis, some things to consider include:

- The structural stability
- The available materials
- Easy access to the battery pack (to replace batteries)
- Plan out where all your components will be located
- Ensure that there is space for wiring

![Chassis gif](../../assets/designing_the_chassis/ezgif.com-gif-maker.gif)

## Laser Cutting and 3D Printing
Once you have finished designing your chassis in Fusion 360, we can laser cut or 3D print your design!

### Converting to .dxf file
To laser cut your Fusion 360 designs, we must first convert it to a .dxf file.

1. Select the sketch that you want to laser cut on the left side bar.
2. Right click the sketch.
3. Save as DXF.

![sketch to dxf](../../assets/designing_the_chassis/laser_cutting_and_3d_printing/sketch_to_dxf.png)

Once you have converted your sketch to a .dxf file, save it onto a USB and take it to the laser cutter to be printed. Make sure to follow all safety procedures before laser cutting.

{: .highlight }
> If you do not have access to the laser cutter, ask the URC Project Lead available.

### Converting to .stl file
If you want to 3D print your design, we must convert your model to an .stl file.

1. Select the body that you want to 3D print on the left side bar.
2. Right click the body.
3. Save as mesh.
![Save as mesh](../../assets/designing_the_chassis/laser_cutting_and_3d_printing/save_as_mesh.png)
4. Choose STL (Binary) as the format and Millimeter as the unit type.
5. Click ok to save!
![Mesh options](../../assets/designing_the_chassis/laser_cutting_and_3d_printing/mesh_options.png)

Once you have an .stl file, we can open it in Ultimaker Cura.

### Ultimaker Cura
Ultimaker Cura is an open-source slicing application for 3D printers, this will turn your CAD model into a format that the 3D printer can understand and create. 

1. To install Ultimaker Cura, click <a href="https://ultimaker.com/software/ultimaker-cura" target="_blank">here</a>.
2. Then click on 'Download for free'.
![Download for free](../../assets/designing_the_chassis/cura/cura_1.png)
3. Choose the correct operating system for your device. This will automatically install the client.
![Choose OS](../../assets/designing_the_chassis/cura/cura_2.png)
4. Click on the client and follow the prompts to finish installing.
![Client](../../assets/designing_the_chassis/cura/cura_3.png)

Once Cura is installed, you can open your .stl file and slice it.

![Slice](../../assets/designing_the_chassis/laser_cutting_and_3d_printing/cura.png)

![Save to disk](../../assets/designing_the_chassis/laser_cutting_and_3d_printing/save_to_disk.png)


{: .highlight }
> Make sure to choose the correct options before slicing. If unsure, ask the available Project Lead.

After slicing, save the .gcode file to an SD card and insert it into the 3D printer to print!
