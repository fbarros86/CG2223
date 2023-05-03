import random
import math
#Sun
xml  = """
<world>
	<window width="1280" height="720" />
	<camera>
	  <position x="-400" y="800" z="-800" />
	  <lookAt x="0" y="0" z="0" />
	  <up x="0" y="1" z="0" />
	  <projection fov="80" near="10" far="5000" />
	</camera>
	<group>
	  <models>
		<model file="sun.3d" /> <!-- Sun (radius=200) -->
	  </models>
"""


#Mercury
MerX = 250
xml+=f"""
<group>
		<transform>
		  <translate time="1" align="true">
        <point x="{MerX}" y="0" z="0"/>
				<point x="{MerX * math.cos(math.pi/4)}" y="0" z="{-MerX * math.sin(math.pi/4)}"/>
				<point x="0" y="0" z="{-MerX}"/>
				<point x="{-MerX * math.cos(math.pi/4)}" y="0" z="{-MerX * math.sin(math.pi/4)}"/>
				<point x="{-MerX}" y="0" z="0"/>
				<point x="{-MerX * math.cos(math.pi/4)}" y="0" z="{MerX * math.sin(math.pi/4)}"/>
				<point x="0" y="0" z="{MerX}"/>
				<point x="{MerX * math.cos(math.pi/4)}" y="0" z="{MerX * math.sin(math.pi/4)}"/>
      </translate>
      <rotate time="59" x="0" y="1" z="0"/>
		</transform>
		<models>
		  <model file="mercury.3d" /> <!-- Mercury (radius=5) -->
		</models>
	  </group>
"""


#Venus
VenusX = 280
xml+=f"""
<group>
		<transform>
		  <translate time="2.55" align="true">
        <point x="{VenusX}" y="0" z="0"/>
				<point x="{VenusX * math.cos(math.pi/4)}" y="0" z="{-VenusX * math.sin(math.pi/4)}"/>
				<point x="0" y="0" z="{-VenusX}"/>
				<point x="{-VenusX * math.cos(math.pi/4)}" y="0" z="{-VenusX * math.sin(math.pi/4)}"/>
				<point x="{-VenusX}" y="0" z="0"/>
				<point x="{-VenusX * math.cos(math.pi/4)}" y="0" z="{VenusX * math.sin(math.pi/4)}"/>
				<point x="0" y="0" z="{VenusX}"/>
				<point x="{VenusX * math.cos(math.pi/4)}" y="0" z="{VenusX * math.sin(math.pi/4)}"/>
      </translate>
      <rotate time="243" x="0" y="1" z="0"/>
		</transform>
		<models>
		  <model file="venus.3d" /> <!-- Venus (radius=8) -->
		</models>
	  </group>
"""



#Earth
EarthX=310
xml+=f"""
<group>
		<transform>
		  <translate time="4.15" align="true">
        <point x="{EarthX}" y="0" z="0"/>
				<point x="{EarthX * math.cos(math.pi/4)}" y="0" z="{-EarthX * math.sin(math.pi/4)}"/>
				<point x="0" y="0" z="{-EarthX}"/>
				<point x="{-EarthX * math.cos(math.pi/4)}" y="0" z="{-EarthX * math.sin(math.pi/4)}"/>
				<point x="{-EarthX}" y="0" z="0"/>
				<point x="{-EarthX * math.cos(math.pi/4)}" y="0" z="{EarthX * math.sin(math.pi/4)}"/>
				<point x="0" y="0" z="{EarthX}"/>
				<point x="{EarthX * math.cos(math.pi/4)}" y="0" z="{EarthX * math.sin(math.pi/4)}"/>
      </translate>
    	<rotate time="1" x="0" y="1" z="0"/>
		</transform>
		<models>
		  <model file="earth.3d" /> <!-- Earth (radius=10) -->
		</models>
		<group>
		  <transform>
			<translate x="20" y="0" z="0" />
		  </transform>
		  <models>
			<model file="earth_moon.3d" /> <!-- Moon (radius=3.5) -->
		  </models>
		</group>
	  </group>
"""

MarsX=350
#Mars
xml+=f"""
<group>
		<transform>
		  <translate time="7.81" align="true">
        <point x="{MarsX}" y="0" z="0"/>
				<point x="{MarsX * math.cos(math.pi/4)}" y="0" z="{-MarsX * math.sin(math.pi/4)}"/>
				<point x="0" y="0" z="{-MarsX}"/>
				<point x="{-MarsX * math.cos(math.pi/4)}" y="0" z="{-MarsX * math.sin(math.pi/4)}"/>
				<point x="{-MarsX}" y="0" z="0"/>
				<point x="{-MarsX * math.cos(math.pi/4)}" y="0" z="{MarsX * math.sin(math.pi/4)}"/>
				<point x="0" y="0" z="{MarsX}"/>
				<point x="{MarsX * math.cos(math.pi/4)}" y="0" z="{MarsX * math.sin(math.pi/4)}"/>
      </translate>
      <rotate time="1" x="0" y="1" z="0"/>
      
		</transform>
		<models>
		  <model file="mars.3d" /> <!-- Mars (radius=6) -->
		</models>
		<group>
		  <transform>
			<translate x="15" y="0" z="0" />
		  </transform>
		  <models>
			<model file="mars_moon.3d" /> <!-- Moon (radius=1.5) -->
		  </models>
    
		</group>
        <group>
		  <transform>
            <rotate angle="95" x="0" y="1" z="0"/>
			<translate x="15" y="0" z="0" />
		  </transform>
		  <models>
			<model file="mars_moon.3d" /> <!-- Moon (radius=1.5) -->
		  </models>
		</group>
	  </group>
"""

#ASTEROID
AsteroidX = 1000
xml+=f"""
<group>
		<transform>
      <rotate angle="45" x="0" y="0" z="1"/>
      <rotate angle="45" x="1" y="0" z="0"/>
      <translate time = "10" align="true"> <!-- O campo align diz se o objecto deve ser orientado na curva -->
				<point x="{AsteroidX}" y="0" z="0"/>
				<point x="{AsteroidX * math.cos(math.pi/4)}" y="0" z="{-AsteroidX * math.sin(math.pi/4)}"/>
				<point x="0" y="0" z="{-AsteroidX}"/>
				<point x="{-AsteroidX * math.cos(math.pi/4)}" y="0" z="{-AsteroidX * math.sin(math.pi/4)}"/>
				<point x="{-AsteroidX}" y="0" z="0"/>
				<point x="{-AsteroidX * math.cos(math.pi/4)}" y="0" z="{AsteroidX * math.sin(math.pi/4)}"/>
				<point x="0" y="0" z="{AsteroidX}"/>
				<point x="{AsteroidX * math.cos(math.pi/4)}" y="0" z="{AsteroidX * math.sin(math.pi/4)}"/>
			</translate>
      <scale x="5" y="5" z="5"/>
		</transform>
		<models>
		  <model file="asteroid.3d" /> <!-- Mars (radius=6) -->
		</models>
	  </group>
"""


#Jupiter
JupiterX=470
xml+=f"""
<group>
		<transform>
			<translate time="49.35" align="true">
        <point x="{JupiterX}" y="0" z="0"/>
				<point x="{JupiterX * math.cos(math.pi/4)}" y="0" z="{-JupiterX * math.sin(math.pi/4)}"/>
				<point x="0" y="0" z="{-JupiterX}"/>
				<point x="{-JupiterX * math.cos(math.pi/4)}" y="0" z="{-JupiterX * math.sin(math.pi/4)}"/>
				<point x="{-JupiterX}" y="0" z="0"/>
				<point x="{-JupiterX * math.cos(math.pi/4)}" y="0" z="{JupiterX * math.sin(math.pi/4)}"/>
				<point x="0" y="0" z="{JupiterX}"/>
				<point x="{JupiterX * math.cos(math.pi/4)}" y="0" z="{JupiterX * math.sin(math.pi/4)}"/>
      </translate>
      <rotate time="0.5" x="0" y="1" z="0"/>
		</transform>
		<models>
		  <model file="jupiter.3d" /> <!-- Jupiter (radius=25) -->
		</models>"""

for i in range(79): 
    x = random.randrange(35,50)
    anglex = random.randrange(0,360)
    angley = random.randrange(0,360)
    anglez = random.randrange(0,360)
    xml+=f"""<group>
		  <transform>
            <rotate angle="{anglex}" x="1" y="0" z="0"/>
            <rotate angle="{angley}" x="0" y="1" z="0"/>
            <rotate angle="{anglez}" x="0" y="0" z="1"/>
			<translate x="{x}" y="0" z="0" />
		  </transform>
		  <models>
			<model file="jupiter_moon.3d" /> <!-- Moon (radius=5) -->
		  </models>
		</group>"""
  
  
xml+="</group>"


SatX=570
#Saturn
xml+=f"""
<group>
		<transform>
		  <translate time="122" align="true">
        <point x="{SatX}" y="0" z="0"/>
				<point x="{SatX * math.cos(math.pi/4)}" y="0" z="{-SatX * math.sin(math.pi/4)}"/>
				<point x="0" y="0" z="{-SatX}"/>
				<point x="{-SatX * math.cos(math.pi/4)}" y="0" z="{-SatX * math.sin(math.pi/4)}"/>
				<point x="{-SatX}" y="0" z="0"/>
				<point x="{-SatX * math.cos(math.pi/4)}" y="0" z="{SatX * math.sin(math.pi/4)}"/>
				<point x="0" y="0" z="{SatX}"/>
				<point x="{SatX * math.cos(math.pi/4)}" y="0" z="{SatX * math.sin(math.pi/4)}"/>
      </translate>
      <rotate time="0.5" x="0" y="1" z="0"/>
		</transform>
		<models>
		  <model file="saturn.3d" /> <!-- Saturn (radius=20) -->
		</models>"""
for i in range(82): 
    lua = random.randrange(1,3)
    x = random.randrange(35,50)
    angley = random.randrange(0,360)
    xml+=f"""<group>
		  <transform>
            <rotate angle="{angley}" x="0" y="1" z="0"/>
			<translate x="{x}" y="0" z="0" />
		  </transform>
		  <models>
			<model file="saturn_moon_{lua}.3d" /> <!-- Moon (radius=2|3.5|4) -->
		  </models>
		</group>"""
  
  
xml+="</group>"


UranusX=700
#Uranus
xml+=f"""
<group>
		<transform>
		  <translate time="348" align="true">
        <point x="{UranusX}" y="0" z="0"/>
				<point x="{UranusX * math.cos(math.pi/4)}" y="0" z="{-UranusX * math.sin(math.pi/4)}"/>
				<point x="0" y="0" z="{-UranusX}"/>
				<point x="{-UranusX * math.cos(math.pi/4)}" y="0" z="{-UranusX * math.sin(math.pi/4)}"/>
				<point x="{-UranusX}" y="0" z="0"/>
				<point x="{-UranusX * math.cos(math.pi/4)}" y="0" z="{UranusX * math.sin(math.pi/4)}"/>
				<point x="0" y="0" z="{UranusX}"/>
				<point x="{UranusX * math.cos(math.pi/4)}" y="0" z="{UranusX * math.sin(math.pi/4)}"/>
      </translate>
      <rotate time="0.7" x="0" y="1" z="0"/>
      
		</transform>
		<models>
		  <model file="uranus.3d" /> <!-- Uranus (radius=15) -->
		</models>"""

for i in range(27): 
    x = random.randrange(25,40)
    anglex = random.randrange(0,360)
    angley = random.randrange(0,360)
    anglez = random.randrange(0,360)
    xml+=f"""<group>
		  <transform>
            <rotate angle="{anglex}" x="1" y="0" z="0"/>
            <rotate angle="{angley}" x="0" y="1" z="0"/>
            <rotate angle="{anglez}" x="0" y="0" z="1"/>
			<translate x="{x}" y="0" z="0" />
		  </transform>
		  <models>
			<model file="uranus_moon.3d" /> <!-- Moon (radius=3) -->
		  </models>
		</group>"""

  
xml+="""
	  </group>
"""

NeptuneX=800
#Neptune
xml+=f"""
<group>
		<transform>
		  <translate time="683" align="true">
        <point x="{NeptuneX}" y="0" z="0"/>
				<point x="{NeptuneX * math.cos(math.pi/4)}" y="0" z="{-NeptuneX * math.sin(math.pi/4)}"/>
				<point x="0" y="0" z="{-NeptuneX}"/>
				<point x="{-NeptuneX * math.cos(math.pi/4)}" y="0" z="{-NeptuneX * math.sin(math.pi/4)}"/>
				<point x="{-NeptuneX}" y="0" z="0"/>
				<point x="{-NeptuneX * math.cos(math.pi/4)}" y="0" z="{NeptuneX * math.sin(math.pi/4)}"/>
				<point x="0" y="0" z="{NeptuneX}"/>
				<point x="{NeptuneX * math.cos(math.pi/4)}" y="0" z="{NeptuneX * math.sin(math.pi/4)}"/>
      </translate>
      <rotate time="0.7" x="0" y="1" z="0"/>
		</transform>
		<models>
		  <model file="neptune.3d" /> <!-- Neptune (radius=14) -->
		</models>"""
  
for i in range(14): 
    x = random.randrange(23,38)
    anglex = random.randrange(0,360)
    angley = random.randrange(0,360)
    anglez = random.randrange(0,360)
    xml+=f"""<group>
		  <transform>
            <rotate angle="{anglex}" x="1" y="0" z="0"/>
            <rotate angle="{angley}" x="0" y="1" z="0"/>
            <rotate angle="{anglez}" x="0" y="0" z="1"/>
			<translate x="{x}" y="0" z="0" />
		  </transform>
		  <models>
			<model file="neptune_moon.3d" /> <!-- Moon (radius=2.5) -->
		  </models>
		</group>"""

  
xml+="""
	  </group>
"""




xml+="""
</group>
	  </world>
"""

file = open('config.xml',"w")
file.write(xml)