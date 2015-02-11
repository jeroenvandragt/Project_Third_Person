print( "Lua file activated" )


function start()
	-- print("Start Function");
	player = getObject("Player");
	enemy1 = getObject("Enemy");
	enemy2 = getObject("Enemy2");
	
	print("waiting 2 seconds to print next");
	--waitForSeconds(2000);
	print("wait another 2 seconds")
	--waitForSeconds(2000);
	print("4 seconds till this has arrived");
	
	
	--[[
	-- test for changing enemy1's position
	print("now we are going to change the position of enemy1");
	--waitForSeconds(3000);
	print("X Position")
	print(getx(enemy1));
	setPosition(enemy1,10,0,10);
	print("position of enemy1 changed to: ")
	print(getx(enemy1));
	say("TESTING FROM LUA TO RENDERSCREEN", 3);
	--]]
	
end


function update()
-- print( "Update Function in Lua" )
	if collide(player,enemy2) then
	print ("Collide");
		waitForSeconds(2000);
		createObject("Enemy3");
		enemy3 = getObject("Enemy3");
		setPosition(enemy3,5,0,-20)
		print ("enemy3 created");
		print (getx(enemy3));
		setMesh(enemy3, "suzanna");
		setTexture(enemy3, "bricks");
		setCollider(enemy3, 1.0);
		setController(enemy3);

		
	end
	
	
	if collide(player,enemy1) then
	print ("hit enemy1")
	destroyObject(enemy1);
	end

end