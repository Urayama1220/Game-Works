<?xml version="1.0" encoding="UTF-8"?>
<moduleList name = "Supporter" version = "1.0">
	<actNode name = "MoveLR">
		<module name = "CheckKeyLRSP" state = "Cnt" key = "LEFT">
			<module name = "CheckColSP" w = "20" speed = "-6" Checkcenterx = "24" Checkcentery = "4">
			<module name = "CheckColSP" w = "32" speed = "-6" Checkcenterx = "24" Checkcentery = "24">
			<module name = "CheckColSP" w = "26" speed = "-6" Checkcenterx = "24" Checkcentery = "42">
				<module name = "CheckCollUnitLRSP" w = "20" speed = "-6" Checkcenterx = "24" Checkcentery = "4">
				<module name = "CheckCollUnitLRSP" w = "32" speed = "-6" Checkcenterx = "24" Checkcentery = "24">
				<module name = "CheckCollUnitLRSP" w = "26" speed = "-6" Checkcenterx = "24" Checkcentery = "42">
					<module  name = "MoveSP" x = "-6"/>
						<module name = "CheckStateSP" state = "Uprun" state2 = "Downrun">
							<module name = "SetAnimeSP" state = "run"/>
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
		<module name = "CheckKeyLRSP" state = "Cnt" key = "RIGHT">
			<module name = "CheckColSP" w = "12" speed = "6" Checkcenterx = "24" Checkcentery = "4">
			<module name = "CheckColSP" w = "16" speed = "6" Checkcenterx = "24" Checkcentery = "24">
			<module name = "CheckColSP" w = "16" speed = "6" Checkcenterx = "24" Checkcentery = "42">
				<module name = "CheckCollUnitLRSP" w = "12" speed = "6" Checkcenterx = "24" Checkcentery = "4">
				<module name = "CheckCollUnitLRSP" w = "16" speed = "6" Checkcenterx = "24" Checkcentery = "24">
				<module name = "CheckCollUnitLRSP" w = "16" speed = "6" Checkcenterx = "24" Checkcentery = "42">
				<module  name = "MoveSP" x = "6"/>
					<module name = "CheckStateSP" state = "Uprun" state2 = "Downrun">
						<module name = "SetAnimeSP" state = "run"/>
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
		<module name = "CheckKeyUDSP" state = "Cnt" key = "Up">
			<module name = "CheckColUSP" w = "12" speed = "-6" Checkcenterx = "8" Checkcentery = "24">
			<module name = "CheckColUSP" w = "34" speed = "-6" Checkcenterx = "24" Checkcentery = "24">
			<module name = "CheckColUSP" w = "12" speed = "-6" Checkcenterx = "36" Checkcentery = "24">
				<module name = "CheckCollUnitUDSP" w = "12" speed = "-6" Checkcenterx = "8" Checkcentery = "24">
				<module name = "CheckCollUnitUDSP" w = "34" speed = "-6" Checkcenterx = "24" Checkcentery = "24">
				<module name = "CheckCollUnitUDSP" w = "24" speed = "-6" Checkcenterx = "36" Checkcentery = "24">
					<module  name = "MoveSP" y = "-6"/>
						<module name = "CheckStateSP" state = "run" state2 = "Downrun">
							<module name = "SetAnimeSP" state = "Uprun"/>
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
		<module name = "CheckKeyUDSP" state = "Cnt" key = "Down">
			<module name = "CheckColDSP" w = "12" speed = "6" Checkcenterx = "8" Checkcentery = "24">
			<module name = "CheckColDSP" w = "22" speed = "6" Checkcenterx = "24" Checkcentery = "24">
			<module name = "CheckColDSP" w = "12" speed = "6" Checkcenterx = "36" Checkcentery = "24">
				<module name = "CheckCollUnitUDSP" w = "12" speed = "6" Checkcenterx = "8" Checkcentery = "24">
				<module name = "CheckCollUnitUDSP" w = "22" speed = "6" Checkcenterx = "24" Checkcentery = "24">
				<module name = "CheckCollUnitUDSP" w = "12" speed = "6" Checkcenterx = "36" Checkcentery = "24">
					<module  name = "MoveSP" y = "6"/>
						<module name = "CheckStateSP" state = "run" state2 = "Uprun">
							<module name = "SetAnimeSP" state = "Downrun"/>
						</module>
				</module>
				</module>
				</module>
			</module>
			</module>
			</module>
		</module>
		
	</actNode>
	
</moduleList>