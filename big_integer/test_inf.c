#include <stdio.h>

int main()
{
    float inf = 1.0f / 0.0f;
    float neg_inf = -1.0f / 0.0f;
    printf( "1.0f / 0.0f %f   \n", inf);
    printf( " inf + inf    %f\n", inf + inf);
    printf( " inf * inf    %f\n", inf * inf);
    printf( " inf + -nef    %f\n", inf + neg_inf);
    printf( " inf + 0    %f\n", inf + 0);
    printf( " inf + 1    %f\n", inf + 1);
    printf( " inf - 0    %f\n", inf - 0);
    printf( " inf - 1    %f\n", inf - 1);
    printf( " inf * 0    %f\n", inf * 0);
    printf( " inf * 1    %f\n", inf * 1);
    printf( " inf / 0.0f %f\n", inf / 0.0f);
    printf( " inf / 1    %f\n", inf / 1);
    //printf( " inf % 0.0f %f\n", inf % 0.0f);
    //printf( " inf % 1    %f\n", inf % 1);

    float nan = inf * 0;
    printf( "inf * 0 %f\n", nan);
    printf( " nan + 0    %f\n", nan + 0);
    printf( " nan + 1    %f\n", nan + 1);
    printf( " nan - 0    %f\n", nan - 0);
    printf( " nan - 1    %f\n", nan - 1);
    printf( " nan * 0    %f\n", nan * 0);
    printf( " nan * 1    %f\n", nan * 1);
    //printf( " nan % 0.0f %f\n", nan % 0.0f);
    //printf( " nan % 1    %f\n", nan % 1);
    
    printf( " nan + inf    %f\n", nan + inf);
    printf( " nan + inf    %f\n", nan + inf);
    printf( " nan - inf    %f\n", nan - inf);
    printf( " nan - inf    %f\n", nan - inf);
    printf( " nan * inf    %f\n", nan * inf);
    printf( " nan * inf    %f\n", nan * inf);
    //printf( " nan % 0.0f %f\n", nan % 0.0f);
    //printf( " nan % 1    %f\n", nan % 1);
    
    printf( "inf <  0  %s\n", inf < 0?"true":"false");
    printf( "inf <= 0  %s\n", inf < 0?"true":"false");
    printf( "inf >  0  %s\n", inf < 0?"true":"false");
    printf( "inf >= 0  %s\n", inf < 0?"true":"false");
    printf( "inf == 0  %s\n", inf < 0?"true":"false");
    printf( "inf != 0  %s\n", inf < 0?"true":"false");

    printf( "inf <  inf  %s\n", inf < inf?"true":"false");
    printf( "inf <= inf  %s\n", inf < inf?"true":"false");
    printf( "inf >  inf  %s\n", inf < inf?"true":"false");
    printf( "inf >= inf  %s\n", inf < inf?"true":"false");
    printf( "inf == inf  %s\n", inf < inf?"true":"false");
    printf( "inf != inf  %s\n", inf < inf?"true":"false");
    
    printf( "inf <  nan  %s\n", inf < nan?"true":"false");
    printf( "inf <= nan  %s\n", inf < nan?"true":"false");
    printf( "inf >  nan  %s\n", inf < nan?"true":"false");
    printf( "inf >= nan  %s\n", inf < nan?"true":"false");
    printf( "inf == nan  %s\n", inf < nan?"true":"false");
    printf( "inf != nan  %s\n", inf < nan?"true":"false");

    printf( "nan <  0  %s\n", nan < 0?"true":"false");
    printf( "nan <= 0  %s\n", nan < 0?"true":"false");
    printf( "nan >  0  %s\n", nan < 0?"true":"false");
    printf( "nan >= 0  %s\n", nan < 0?"true":"false");
    printf( "nan == 0  %s\n", nan < 0?"true":"false");
    printf( "nan != 0  %s\n", nan < 0?"true":"false");
    
    float div = 1 / inf;
    printf( "div %f\n", div);
    return 0;
}
