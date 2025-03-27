modded class AreaExposureMdfr
{
	override void ApplyAgentsToBleedingSources(PlayerBase player, float deltaT)
	{
		int count = player.GetBleedingSourceCount();
		float agent_dose = count * AGENT_DOSE_PER_BS_SEC * deltaT;
		
		// Check gas mask
		if (player.FindAttachmentBySlotName("Mask"))
		{
			Clothing maskClothes = Clothing.Cast(player.FindAttachmentBySlotName("Mask"));
			if (maskClothes && maskClothes.IsGasMask())
			{
				MaskBase mask = MaskBase.Cast(maskClothes);	
				if(mask.HasValidFilter())
				{
					agent_dose = 0;
				}
			}
		}
		
		player.InsertAgent(eAgents.CHEMICAL_POISON, agent_dose);
		//Print("ApplyAgentsToBleedingSources! count:" + count + ", dose:" + agent_dose);	//DEBUG
	}
	
	override float TransmitAgents(PlayerBase player, float count)
	{	
		// Check gas mask
		if (player.FindAttachmentBySlotName("Mask"))
		{
			Clothing maskClothes = Clothing.Cast(player.FindAttachmentBySlotName("Mask"));
			if (maskClothes && maskClothes.IsGasMask())
			{
				MaskBase mask = MaskBase.Cast(maskClothes);	
				if(mask.HasValidFilter())
				{
					count = 0;
					//Print("TransmitAgents - found MASK so zero count");	//DEBUG
				}
			}
		}
		PluginTransmissionAgents plugin = PluginTransmissionAgents.Cast(GetPlugin(PluginTransmissionAgents));
		return plugin.TransmitAgentsEx(null, player, AGT_AIRBOURNE_CHEMICAL, count, eAgents.CHEMICAL_POISON);
	}
	
	override void BleedingSourceCreateCheck(PlayerBase player)
	{
		int free_bs_locations = 0;//bitmask where each bit set to 1 represents available bleeding source location
		set<int> list = player.GetBleedingManagerServer().GetBleedingSourcesLocations();
		
		foreach(int location: list)
		{
			float prot_level = PluginTransmissionAgents.GetProtectionLevelEx(DEF_CHEMICAL, location, player, true);
			float dice_throw = Math.RandomFloat01();
			if(dice_throw > prot_level)
			{
				free_bs_locations = player.GetBleedingManagerServer().GetFreeBleedingSourceBitsByInvLocation(location) | free_bs_locations;
			}
		}
		
		int num_of_free_bs = Math.GetNumberOfSetBits(free_bs_locations);//gets us the number of bits set to 1, where each represents a free bleeding source location
		
		// Check gas mask
		if (player.FindAttachmentBySlotName("Mask"))
		{
			Clothing maskClothes = Clothing.Cast(player.FindAttachmentBySlotName("Mask"));
			if (maskClothes && maskClothes.IsGasMask())
			{
				MaskBase mask = MaskBase.Cast(maskClothes);	
				if(mask.HasValidFilter())
				{
					//Print("BleedingSourceCreateCheck - found MASK so zero free_bs");	//DEBUG
					num_of_free_bs = 0;
				}
			}
		}
				
		if ( num_of_free_bs > 0 )
		{
			int random_bs_index = Math.RandomIntInclusive(0, num_of_free_bs - 1 );// - 1 on the max to convert count to index
			int random_bs_bit = Math.Pow(2, Math.GetNthBitSet(free_bs_locations,random_bs_index));
			player.GetBleedingManagerServer().AttemptAddBleedingSourceDirectly(random_bs_bit, eBleedingSourceType.CONTAMINATED);
		}
	}
};