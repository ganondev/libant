qt_node_comparison_result_t qt_node_compare(qt_node_t * reference, qt_node_t * target)
{

	#ifdef TREEBUG
	printf("Comparing node at (%lld, %lld) to reference node at (%lld, %lld).", target->x, target->y, reference->x, reference->y);
	#endif
	if (reference->y == target->y && reference->x == target->x) return EQ;
	
	bool vertical = reference->y > target->y;
	bool horizontal = reference->x > target->x;

	return (vertical * 2) | horizontal;

}