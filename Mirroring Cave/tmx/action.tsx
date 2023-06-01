<?xml version="1.0" encoding="UTF-8"?>
<moduleList name = "Player" version = "1.0">
	<actNode name = "MoveLR">
		<module name = "CheckKeyLR" state = "Cnt" key = "LEFT">
			<module name = "CheckCol" w = "26" speed = "-6" Checkcenterx = "24" Checkcentery = "6">
			<module name = "CheckCol" w = "26" speed = "-6" Checkcenterx = "24" Checkcentery = "24">
			<module name = "CheckCol" w = "26" speed = "-6" Checkcenterx = "24" Checkcentery = "42">
				<module name = "CheckCollUnitLR" w = "26" speed = "-6" Checkcenterx = "24" Checkcentery = "6">
				<module name = "CheckCollUnitLR" w = "26" speed = "-6" Checkcenterx = "24" Checkcentery = "24">
				<module name = "CheckCollUnitLR" w = "26" speed = "-6" Checkcenterx = "24" Checkcentery = "42">
						<module  name = "Move" x = "-6"/>
						<module name = "CheckState" state = "Uprun" state2 = "Downrun">
							<module name = "SetAnime" state = "run"/>
						</module>
				</module>
				</module>
				</module>
			</module>
			</module>
			</module>
		</module>
		
	</actNode>
	<actNode name = "MoveLR">
		<module name = "CheckKeyLR" state = "Cnt" key = "RIGHT">
			<module name = "CheckCol" w = "18" speed = "6" Checkcenterx = "24" Checkcentery = "6">
			<module name = "CheckCol" w = "16" speed = "6" Checkcenterx = "24" Checkcentery = "24">
			<module name = "CheckCol" w = "12" speed = "6" Checkcenterx = "24" Checkcentery = "42">
				<module name = "CheckCollUnitLR" w = "12" speed = "6" Checkcenterx = "24" Checkcentery = "6">
				<module name = "CheckCollUnitLR" w = "18" speed = "6" Checkcenterx = "24" Checkcentery = "24">
				<module name = "CheckCollUnitLR" w = "10" speed = "6" Checkcenterx = "24" Checkcentery = "42">
						<module  name = "Move" x = "6"/>
						<module name = "CheckState" state = "Uprun" state2 = "Downrun">
							<module name = "SetAnime" state = "run"/>
						</module>
				</module>
				</module>
				</module>
			</module>
			</module>
			</module>
		</module>
		
	</actNode>
	<actNode name = "MoveUD">
		<module name = "CheckKeyUD" state = "Cnt" key = "Up">
			<module name = "CheckColUD" w = "32" speed = "-6" Checkcenterx = "12" Checkcentery = "24">
			<module name = "CheckColUD" w = "32" speed = "-6" Checkcenterx = "24" Checkcentery = "24">
			<module name = "CheckColUD" w = "32" speed = "-6" Checkcenterx = "36" Checkcentery = "24">
				<module name = "CheckCollUnitUD" w = "32" speed = "-6" Checkcenterx = "12" Checkcentery = "24">
				<module name = "CheckCollUnitUD" w = "32" speed = "-6" Checkcenterx = "24" Checkcentery = "24">
				<module name = "CheckCollUnitUD" w = "32" speed = "-6" Checkcenterx = "36" Checkcentery = "24">
						<module  name = "Move" y = "-6"/>
					<module name = "CheckState" state = "run" state2 = "Downrun">
						<module name = "SetAnime" state = "Uprun"/>
					</module>
				</module>
				</module>
				</module>
			</module>
			</module>
			</module>
		</module>
		
	</actNode>
	
	<actNode name = "MoveUD">
		<module name = "CheckKeyUD" state = "Cnt" key = "Down">
			<module name = "CheckColD" w = "22" speed = "6" Checkcenterx = "12" Checkcentery = "24">
			<module name = "CheckColD" w = "22" speed = "6" Checkcenterx = "24" Checkcentery = "24">
			<module name = "CheckColD" w = "22" speed = "6" Checkcenterx = "36" Checkcentery = "24">
				<module name = "CheckCollUnitUD" w = "22" speed = "6" Checkcenterx = "12" Checkcentery = "24">
				<module name = "CheckCollUnitUD" w = "22" speed = "6" Checkcenterx = "24" Checkcentery = "24">
				<module name = "CheckCollUnitUD" w = "22" speed = "6" Checkcenterx = "36" Checkcentery = "24">
						<module  name = "Move" y = "6"/>
						<module name = "CheckState" state = "run" state2 = "Uprun">
							<module name = "SetAnime" state = "Downrun"/>
						</module>
				</module>
				</module>
				</module>
			</module>
			</module>
			</module>
		</module>
		
	</actNode>
	<actNode name = "Checkdie">
		<module name = "Checkdead" >
			<module name = "SetAnime" state = "Die"/>
		</module>
		
	</actNode>
</moduleList>