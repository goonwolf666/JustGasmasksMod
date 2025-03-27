modded class PluginTransmissionAgents //extends PluginBase
{
	override protected float InjectAgentWithPlayerDose(EntityAI target, int agent, float protection, float dose_size, int inject_type)//target,array_of_agents,protection_lvl
	{
		//Print("PluginTransmission IAWPD! agent:" + agent + ", protection:" + protection + ", dose_size:" + dose_size + ", inject_type:" + inject_type);//DEBUG		
		
		// Check gas mask
		if (target.FindAttachmentBySlotName("Mask"))
		{
			Clothing maskClothes = Clothing.Cast(target.FindAttachmentBySlotName("Mask"));
			if (maskClothes && maskClothes.IsGasMask())
			{
				MaskBase mask = MaskBase.Cast(maskClothes);	
				if(mask.HasValidFilter() && inject_type == 2)
				{
					//Print("InjectAgentWithPlayerDose - found MASK and AIR injectable type so zero dose!"); //DEBUG
					dose_size = 0;
				}
			}
		}
		
		float count = CalculateAgentsToTransmit(agent, protection, dose_size, inject_type);
		{
			if(count > 0)
			{
				target.InsertAgent(agent, count);
				return count;
			}
		}
		return 0;
	}
};