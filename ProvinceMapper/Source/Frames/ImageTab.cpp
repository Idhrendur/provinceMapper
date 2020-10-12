#include "ImageTab.h"
#include "OSCompatibilityLayer.h"
#include <wx/wrapsizer.h>

ImageTab::ImageTab(wxWindow* parent, ImageTabSelector theSelector, const std::shared_ptr<LinkMappingVersion>& theActiveVersion):
	 wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
{
	// ImageTab is a notebook page, that will contain the actual image. 
	
	wxWrapSizer* imageTabSizer = new wxWrapSizer(wxBOTH); // It will use a WrapSizer, which is just a box around something, that can expand in both directions.
	SetScrollRate(16, 16);

	if (theSelector == ImageTabSelector::SOURCE)
	{
		wxImage image; // We load an image
		image.LoadFile("test-from/provinces.bmp", wxBITMAP_TYPE_BMP);
		imageBox = new ImageBox(this, image, theSelector, theActiveVersion);
		imageTabSizer->Add(imageBox); // Add the image to the sizer
		imageBox->SetMinSize(image.GetSize()); // and set minimum size to the size if the image we loaded, so everything displays at once.
		Log(LogLevel::Debug) << "loaded from " << image.GetSize().GetX() << "x" << image.GetSize().GetY();
	}
	if (theSelector == ImageTabSelector::TARGET)
	{
		wxImage image;
		image.LoadFile("test-to/provinces.bmp", wxBITMAP_TYPE_BMP);
		imageBox = new ImageBox(this, image, theSelector, theActiveVersion);
		imageTabSizer->Add(imageBox);
		imageBox->SetMinSize(image.GetSize());
		Log(LogLevel::Debug) << "loaded to " << image.GetSize().GetX() << "x" << image.GetSize().GetY();
	}

	SetSizer(imageTabSizer); // Here we register the sizer with our ImageTab.
}

void ImageTab::refresh()
{
	imageBox->paintNow();
}
