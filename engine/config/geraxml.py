import random
#Sun
xml  = """
<world>
	<window width="1280" height="720" />
	<camera>
	  <position x="800" y="100" z="100" />
	  <lookAt x="0" y="0" z="100" />
	  <up x="0" y="1" z="0" />
	  <projection fov="80" near="10" far="5000" />
	</camera>
	<group>
	  <models>
		<model file="sun.3d" /> <!-- Sun (radius=200) -->
	  </models>

"""


#Mercury
xml+="""
<group>
		<transform>
		  <translate time="1" align="true">
            <point x="210" y="0" z="0"/>
            <point x="0" y="0" z="210"/>
            <point x="-210" y="0" z="0"/>
            <point x="0" y="0" z="-210"/>
      </translate>
      <rotate time="59" x="0" y="1" z="0"/>
		</transform>
		<models>
		  <model file="mercury.3d" /> <!-- Mercury (radius=5) -->
		</models>
	  </group>
"""


#Venus
xml+="""
<group>
		<transform>
          <rotate angle="-8" x="1" y="0" z="0"/>
      <rotate angle="-18.75" x="0" y="1" z="0"/>
		  <translate time="2.55" align="true">
            <point x="230" y="0" z="0"/>
            <point x="0" y="0" z="230"/>
            <point x="-230" y="0" z="0"/>
            <point x="0" y="0" z="-230"/>
      </translate>
      <rotate time="243" x="0" y="1" z="0"/>
		</transform>
		<models>
		  <model file="venus.3d" /> <!-- Venus (radius=8) -->
		</models>
	  </group>

"""



#Earth
xml+="""
<group>
		<transform>
  <rotate angle="-16" x="1" y="0" z="0"/>
      <rotate angle="-37.5" x="0" y="1" z="0"/>
		  <translate time="4.15" align="true">
            <point x="260" y="0" z="0"/>
            <point x="0" y="0" z="260"/>
            <point x="-260" y="0" z="0"/>
            <point x="0" y="0" z="-260"/>
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


#Mars
xml+="""
<group>
		<transform>
  <rotate angle="-20" x="1" y="0" z="0"/>
      <rotate angle="-56.25" x="0" y="1" z="0"/>
		  <translate time="7.81" align="true">
            <point x="300" y="0" z="0"/>
            <point x="0" y="0" z="300"/>
            <point x="-300" y="0" z="0"/>
            <point x="0" y="0" z="-300"/>
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
'''
#ASTEROID
xml+="""
<group>
		<transform>
  <rotate angle="-20" x="1" y="0" z="0"/>
      <rotate angle="-56.25" x="0" y="1" z="0"/>
		  <translate x="300" y="0" z="0" />
          <scale x="400" y="400" z="400"/>
          <translate time = "10" align="true"> <!-- O campo align diz se o objecto deve ser orientado na curva -->
					<point x = "0" y = "0" z = "4" />
					<point x = "4" y = "0" z = "0" />
					<point x = "0" y = "0" z = "-4" />
					<point x = "-4" y = "10" z = "0" />
			</translate>
		</transform>
		<models>
		  <model file="asteroid.3d" /> <!-- Mars (radius=6) -->
		</models>
	  </group>
"""
'''

#Jupiter
xml+="""
<group>
		<transform>
      <rotate angle="-20" x="1" y="0" z="0"/>
      <rotate angle="-75" x="0" y="1" z="0"/>
			<translate time="49.35" align="true">
            <point x="370" y="0" z="0"/>
            <point x="0" y="0" z="370"/>
            <point x="-370" y="0" z="0"/>
            <point x="0" y="0" z="-370"/>
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



#Saturn
xml+="""
<group>
		<transform>
        <rotate angle="-20" x="1" y="0" z="0"/>
      <rotate angle="-93.75" x="0" y="1" z="0"/>
		  <translate time="122" align="true">
            <point x="470" y="0" z="0"/>
            <point x="0" y="0" z="470"/>
            <point x="-470" y="0" z="0"/>
            <point x="0" y="0" z="-470"/>
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



#Uranus
xml+="""
<group>
		<transform>
          <rotate angle="-20" x="1" y="0" z="0"/>

      <rotate angle="-131.25" x="0" y="1" z="0"/>

		  <translate time="348" align="true">
            <point x="600" y="0" z="0"/>
            <point x="0" y="0" z="600"/>
            <point x="-600" y="0" z="0"/>
            <point x="0" y="0" z="-600"/>
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


#Neptune
xml+="""
<group>
		<transform>
      <rotate angle="-150" x="0" y="1" z="0"/>
		  <translate time="683" align="true">
            <point x="700" y="0" z="0"/>
            <point x="0" y="0" z="700"/>
            <point x="-700" y="0" z="0"/>
            <point x="0" y="0" z="-700"/>
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