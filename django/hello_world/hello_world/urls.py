from django.conf.urls import patterns, include, url
from hello_world import views

# Uncomment the next two lines to enable the admin:
# from django.contrib import admin
# admin.autodiscover()

urlpatterns = patterns('',
    url(r'^$', views.index),
    url(r'^hello/$', views.hello),
    url(r'^time/$', views.time),
    url(r'^time/plus/(-?\d{1,3})/$', views.time_plus),
    # Examples:
    # url(r'^$', 'hello_world.views.home', name='home'),
    # url(r'^hello_world/', include('hello_world.foo.urls')),

    # Uncomment the admin/doc line below to enable admin documentation:
    # url(r'^admin/doc/', include('django.contrib.admindocs.urls')),

    # Uncomment the next line to enable the admin:
    # url(r'^admin/', include(admin.site.urls)),
)