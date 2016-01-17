/*----------------------------------------------------------------------------
 * File:  masl_population_class.c
 *
 * Class:       population  (population)
 * Component:   masl
 *
 * your copyright statement can go here (from te_copyright.body)
 *--------------------------------------------------------------------------*/

#include "masl_sys_types.h"
#include "LOG_bridge.h"
#include "STRING_bridge.h"
#include "T_bridge.h"
#include "TRACE_bridge.h"
#include "masl_classes.h"

/*
 * class operation:  populate
 */
void
masl_population_op_populate( c_t p_element[ESCHER_SYS_MAX_STRING_LEN], c_t p_value[8][ESCHER_SYS_MAX_STRING_LEN] )
{
  c_t * value[8]={0,0,0,0,0,0,0,0};c_t * element=0;masl_population * population=0;
int i;
printf("masl_population_op_populate:  %s",p_element);
for(i=0;i<8;i++) { if (p_value[i][0]) { printf(",%s",p_value[i]); } else { break; }}
printf("\n");
  /* ASSIGN element = PARAM.element */
  element = p_element;
  /* ASSIGN value = PARAM.value */
  value[0] = p_value[0];
  value[1] = p_value[1];
  value[2] = p_value[2];
  value[3] = p_value[3];
  /* SELECT any population FROM INSTANCES OF population */
  population = (masl_population *) Escher_SetGetAny( &pG_masl_population_extent.active );
  /* IF ( empty population ) */
  if ( ( 0 == population ) ) {
    /* CREATE OBJECT INSTANCE population OF population */
    population = (masl_population *) Escher_CreateInstance( masl_DOMAIN_ID, masl_population_CLASS_NUMBER );
  }
  /* IF ( ( project == element ) ) */
  if ( ( Escher_strcmp( "project", element ) == 0 ) ) {
    /* ASSIGN population.project = project::populate(name:value[0]) */
    population->project = masl_project_op_populate(value[0]);
  }
  else if ( ( Escher_strcmp( "domain", element ) == 0 ) ) {
    /* ASSIGN population.domain = domain::populate(name:value[0], project:population.project) */
    population->domain = masl_domain_op_populate(value[0], population->project);
  }
  else if ( ( Escher_strcmp( "object", element ) == 0 ) ) {
    /* ASSIGN population.object = object::populate(domain:population.domain, name:value[0]) */
    population->object = masl_object_op_populate(population->domain, value[0]);
  }
  else if ( ( Escher_strcmp( "terminator", element ) == 0 ) ) {
    /* ASSIGN population.terminator = terminator::populate(domain:population.domain, name:value[0]) */
    population->terminator = masl_terminator_op_populate(population->domain, value[0]);
  }
  else if ( ( Escher_strcmp( "activity", element ) == 0 ) ) {
    /* IF ( (  != value[1] ) ) */
    if ( ( Escher_strcmp( "", value[1] ) != 0 ) ) {
      /* ASSIGN population.activity = activity::populate(flavor:value[2], name:value[0], terminator:population.terminator) */
      population->activity = masl_activity_op_populate(value[2], value[0], population->terminator);
    }
    else if ( FALSE ) {
    }
    else if ( FALSE ) {
    }
    else {
      /* TRACE::log( flavor:failure, id:40, message:( unrecognized activity:   + value[0] ) ) */
      TRACE_log( "failure", 40, Escher_stradd( "unrecognized activity:  ", value[0] ) );
    }
  }
  else if ( ( Escher_strcmp( "parameter", element ) == 0 ) ) {
    /* IF ( (  == value[3] ) ) */
    if ( ( Escher_strcmp( "", value[3] ) == 0 ) ) {
      masl_parameter * empty_parameter=0;
      /* SELECT any empty_parameter FROM INSTANCES OF parameter WHERE FALSE */
      empty_parameter = 0;
      /* ASSIGN population.parameter = parameter::populate(activity:population.activity, direction:value[2], name:value[0], previous_parameter:empty_parameter, type:value[1]) */
      population->parameter = masl_parameter_op_populate(population->activity, value[2], value[0], empty_parameter, value[1]);
    }
    else {
      /* ASSIGN population.parameter = parameter::populate(activity:population.activity, direction:value[2], name:value[0], previous_parameter:population.parameter, type:value[1]) */
      population->parameter = masl_parameter_op_populate(population->activity, value[2], value[0], population->parameter, value[1]);
    }
  }
  else if ( ( Escher_strcmp( "attribute", element ) == 0 ) ) {
    /* ASSIGN population.attribute = attribute::populate(defaultvalue:value[3], name:value[0], object:population.object, preferred:value[1], unique:value[2]) */
    population->attribute = masl_attribute_op_populate(value[3], value[0], population->object, value[1], value[2]);
  }
  else {
    /* TRACE::log( flavor:failure, id:39, message:( unrecognized element:   + element ) ) */
    TRACE_log( "failure", 39, Escher_stradd( "unrecognized element:  ", element ) );
  }
}


/*----------------------------------------------------------------------------
 * Operation action methods implementation for the following class:
 *
 * Class:      population  (population)
 * Component:  masl
 *--------------------------------------------------------------------------*/
/*
 * Statically allocate space for the instance population for this class.
 * Allocate space for the class instance and its attribute values.
 * Depending upon the collection scheme, allocate containoids (collection
 * nodes) for gathering instances into free and active extents.
 */
static Escher_SetElement_s masl_population_container[ masl_population_MAX_EXTENT_SIZE ];
static masl_population masl_population_instances[ masl_population_MAX_EXTENT_SIZE ];
Escher_Extent_t pG_masl_population_extent = {
  {0}, {0}, &masl_population_container[ 0 ],
  (Escher_iHandle_t) &masl_population_instances,
  sizeof( masl_population ), 0, masl_population_MAX_EXTENT_SIZE
  };

